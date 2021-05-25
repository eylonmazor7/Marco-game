#include "Board.h"
#include <fstream>

const Options Board::checkTerms()
{
	if (m_Marco.getHP() <= 0)
	{
		cleanDetails(false);
		return Options::OutOfLife;
	}

	else if (m_Marco.getReady())
	{
		cleanDetails(false);
		return Options::MarcoSuccsess;
	}
	return Options::Nothing;
}

void Board::cleanDetails(bool newgame)
{
	m_bossBullets.clear();
	m_ownerBullets.clear();
	m_marcoBullets.clear();
	m_staticObject.clear();
	m_Owners.clear();
	m_Bombs.clear();
	m_Trans.clear();
	m_FreePlaces.clear();
	m_Marco.restartKeys();
	m_Boss.setExist(false);

	if (newgame)
	{
		m_Marco.setDetails();
		m_Marco.setSpeed(Speed::MARCO_SPEED);
		m_Kofifo.setSpeed(Speed::KOFIFO_SPEED);
	}
}

void Board::drawObject(sf::RenderWindow& window) const
{
	m_Marco.draw(window);

	for (int i = 0; i < m_marcoBullets.size(); i++)
		m_marcoBullets[i]->draw(window);
	for (int i = 0; i < m_ownerBullets.size(); i++)
		m_ownerBullets[i]->draw(window);
	for (int i = 0; i < m_Owners.size(); i++)
		m_Owners[i]->draw(window);
	for (int i = 0; i < m_Bombs.size(); i++)
	{
		m_Bombs[i]->draw(window);
		window.draw(m_Bombs[i]->getCir());
	}
	for (int i = 0; i < m_Trans.size(); i++)
		m_Trans[i]->draw(window);

	for (int i = 0; i < m_staticObject.size(); i++)
		if (m_staticObject[i]->getExist())
			m_staticObject[i]->draw(window);
	
	m_Kofifo.draw(window);

	if (m_Boss.getExist())
		m_Boss.draw(window);
	for (int i = 0; i < m_bossBullets.size(); i++)
		m_bossBullets[i]->draw(window);
}

void Board::getDetails(struct Details& d) const
{
	d.ammo = m_Marco.getBulletsCapacity();
	d.bomb = m_Marco.getBombsCapacity();
	d.food = m_Marco.getFood();
	d.HP = m_Marco.getHP();
	d.money = m_Marco.getMoney();
	d.tele = m_Marco.getTransTimes();
	d.keys = m_Marco.getTreasureKey();
}

void Board::eraseObject()
{
	auto marcoKilled = m_Owners.size();
	auto delFunc = [](auto& dataBase)
	{
		for (int i = 0; i < dataBase.size();)
			if (!dataBase[i]->getExist())
				dataBase.erase(dataBase.begin() + i);
			else
				i++;
	};

	delFunc(m_staticObject);
	delFunc(m_marcoBullets);
	delFunc(m_ownerBullets);
	delFunc(m_bossBullets);
	delFunc(m_Owners);
	delFunc(m_Bombs);
	delFunc(m_Trans);

	m_Marco.setMoney((int)(marcoKilled - m_Owners.size()) * 10);
}

void Board::moveObject(const float deltaTime)
{
	auto kofDirectionToMarco = checkDirectionToMarco(m_Kofifo.getCurrPos());
	
	sf::Vector2f n{ 0,0 }; 

	m_Marco.moveObject(deltaTime, n);
	m_Marco.startAnimation(50, 150);
	m_Kofifo.moveObject(deltaTime, kofDirectionToMarco);
	m_Kofifo.startAnimation(47, 94);
	
	if (m_Boss.getExist())
	{
		auto bossDirectionToMarco = checkDirectionToMarco(m_Boss.getCurrPos());
		m_Boss.moveObject(deltaTime, bossDirectionToMarco);
		m_Boss.startAnimation(50, 100);
	}

	for (int i = 0; i < m_Owners.size(); i++)
	{
		auto directionToMarco = checkDirectionToMarco(m_Owners[i]->getCurrPos());
		m_Owners[i]->moveObject(deltaTime, directionToMarco);
		m_Owners[i]->startAnimation(37, 259);
	}

	for (int i = 0; i < m_bossBullets.size(); i++)
	{
		m_bossBullets[i]->bossFire();
		if (calcDistance(m_bossBullets[i]->getStartPos(), m_bossBullets[i]->getCurr()) > Weapons::BOSS_BULLET_RANGE)
			m_bossBullets[i]->setExist(false);
	}

	for (int i = 0; i < m_ownerBullets.size(); i++)
		m_ownerBullets[i]->fire();

	for (int i = 0; i < m_marcoBullets.size(); i++)
		m_marcoBullets[i]->fire();

	for (int i = 0; i < m_Bombs.size(); i++)
	{
		if (!m_Bombs[i]->timeToBlow())
			continue;

		m_Bombs[i]->blow();
		if(!m_Bombs[i]->getExist())
			checkBombEffect(i);
	}

	for (int i = 0; i < m_Trans.size(); i++)
	{
		m_Trans[i]->transform();
		dealWithSound(Sounds::flash);
	}
			
	if (m_Trans.size() > 0)
		m_Marco.setCurrPos(m_FreePlaces[rand() % m_FreePlaces.size()]);

	if (m_Kofifo.getChangePos())
	{
		m_Kofifo.changePos(false);
		
		auto tempPos = m_FreePlaces[rand() % m_FreePlaces.size()];
		
		while (calcDistance(m_Kofifo.getCurrPos(), tempPos) >= Utilities::KOFIFO_DISTANCE)
			tempPos = m_FreePlaces[rand() % m_FreePlaces.size()];

		m_Kofifo.setCurrPos(tempPos);
	}
}

void Board::checkBombEffect(int whichBomb)
{
	auto BombPos = m_Bombs[whichBomb]->getStartPos();
	if (calcDistance(m_Marco.getCurrPos(), BombPos) <= Weapons::BOMB_RADIUS)
		m_Marco.setHP(Weapons::BOMB_EFFECTS);
	
	for (int i = 0; i < m_Owners.size(); i++)
		if (calcDistance(m_Owners[i]->getCurrPos(), BombPos) <= Weapons::BOMB_RADIUS)
			m_Owners[i]->setHP(Weapons::BOMB_EFFECTS);

	if (m_Boss.getExist())
		if (calcDistance(BombPos, m_Boss.getCurrPos()))
			m_Boss.setHP(Weapons::BOMB_EFFECTS);
}

void Board::dealWithBullet(sf::Vector2f mousePos)
{
	if (!m_Marco.getBulletsCapacity())
		return;

	m_Marco.setBulletsCapacity(-1);

	auto temp = mousePos - m_Marco.getCurrPos();
	auto normDir = temp / sqrt((pow(temp.x, 2) + pow(temp.y, 2)));
	normDir.x *= Speed::MARCO_BULLET_SPEED;
	normDir.y *= Speed::MARCO_BULLET_SPEED;
	
	m_marcoBullets.push_back(std::make_unique<MarcoBullet>(m_Marco.getCurrPos(), 
			m_BulletSprite, normDir));
}

void Board::dealWithBomb()
{
	if (!m_Marco.getBombsCapacity())
		return;

	m_Marco.setBombsCapacity(-1);

	m_Bombs.push_back(std::make_unique<Bomb>
		(getMarcoPos(), ToolBar::instance().getPicture('L')));

	dealWithSound(Sounds::bombSound);
}

void Board::dealWithTrans()
{
	if (!m_Marco.getTransTimes())
		return;
	m_Marco.setTrans(-1);
	m_Trans.push_back(std::make_unique<Teleport>
		(getMarcoPos(), ToolBar::instance().getPicture('M')));
}

void Board::changeBulletPic(Guns kind)
{
	switch (kind)
	{
	case Guns::Fire:
		m_BulletSprite = ToolBar::instance().getPicture(UtilitiesChar::C_ANOTHERBULLET);
		break;

	case Guns::Blue:
		m_BulletSprite = ToolBar::instance().getPicture(UtilitiesChar::C_BULLET);
		break;

	case Guns::Yellow:
		m_BulletSprite = ToolBar::instance().getPicture(UtilitiesChar::C_ANOTHERBULLET2);
		break;
	}
}

void Board::ownerTurn()
{
	for (int i = 0; i < m_Owners.size(); i++)
	{
		double distance = calcDistance(m_Marco.getCurrPos(), m_Owners[i]->getCurrPos());

		sf::Vector2f directionToMarco = checkDirectionToMarco(m_Owners[i]->getCurrPos());
		directionToMarco.x *= Speed::OWNER_BULLET_SPEED;
		directionToMarco.y *= Speed::OWNER_BULLET_SPEED;

		if (!m_Owners[i]->getExist())
			continue;

		if(rand() % 100 > Weapons::OWNER_RATE_OF_FIRE)
				if (distance < Weapons::SHOOTING_RANGE)
					m_ownerBullets.push_back(std::make_unique<OwnerBullet>(m_Owners[i]->getCurrPos(),
						ToolBar::instance().getPicture(UtilitiesChar::C_BULLET), directionToMarco));
	}

	if (m_Boss.getExist())
	{
		double distance = calcDistance(m_Marco.getCurrPos(), m_Boss.getCurrPos());
		sf::Vector2f directionToMarco = checkDirectionToMarco(m_Boss.getCurrPos());
		directionToMarco.x *= Speed::BOSS_BULLET_SPEED;
		directionToMarco.y *= Speed::BOSS_BULLET_SPEED;

		if (distance < (Weapons::SHOOTING_RANGE * 2))
			if (rand() % 100 > Weapons::BOSS_RATE_OF_FIRE)
				m_bossBullets.push_back(std::make_unique<BossBullet>(m_Boss.getCurrPos(),
					ToolBar::instance().getPicture(UtilitiesChar::C_BOSSBULLET), directionToMarco));
	}
}

double Board::calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2) const
{
	return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

sf::Vector2f Board::checkDirectionToMarco(const sf::Vector2f& objectPos) const
{	
	auto marcoPos = m_Marco.getCurrPos();
	auto temp = marcoPos - objectPos;
	auto normDir = temp / sqrt((pow(temp.x, 2) + pow(temp.y, 2)));
	return normDir;
}

void Board::checkCollision()
{
	auto colFunc = [](Object& a, Object& b) { Collision::instance().CollisionFunc(a, b); };

	auto helpFunc = [](auto& dataBase, Object& temp, auto func)
	{
		for (int i = 0; i < dataBase.size(); i++)
		{
			if (CheckCollision::PixelPerfectTest(temp.getSprite(), dataBase[i]->getSprite()))
				func(temp, *dataBase[i].get());
		}
	};
			
	helpFunc(m_staticObject, m_Marco, colFunc);
	helpFunc(m_ownerBullets, m_Marco, colFunc);
	helpFunc(m_staticObject, m_Kofifo, colFunc);
	helpFunc(m_Owners, m_Marco, colFunc);

	for (int k = 0; k < m_Owners.size(); k++)
		helpFunc(m_staticObject, *m_Owners[k].get(), colFunc);
		
	for (int k = 0; k < m_Owners.size(); k++)
		helpFunc(m_marcoBullets, *m_Owners[k].get(), colFunc);
			
	for (int k = 0; k < m_marcoBullets.size(); k++)
		helpFunc(m_staticObject, *m_marcoBullets[k].get(), colFunc);

	for (int k = 0; k < m_ownerBullets.size(); k++)
		helpFunc(m_staticObject, *m_ownerBullets[k].get(), colFunc);

	if (CheckCollision::PixelPerfectTest(m_Marco.getSprite(), m_Kofifo.getSprite()))
	{
		colFunc(m_Marco, m_Kofifo);
		dealWithSound(Sounds::points);
	}

	if (m_Boss.getExist())
	{
		if (CheckCollision::PixelPerfectTest(m_Marco.getSprite(), m_Boss.getSprite()))
			colFunc(m_Marco, m_Boss);

		helpFunc(m_marcoBullets, m_Boss, colFunc);
		helpFunc(m_bossBullets, m_Marco, colFunc);
		helpFunc(m_staticObject, m_Boss, colFunc);
	}

}

float Board::getHeight() const
{
	return m_rowSize* Utilities::SIZE_OF_PIC;
}

float Board::getWidth() const
{
	return m_colSize * Utilities::SIZE_OF_PIC;
}

const sf::Vector2f Board::getMarcoPos() const //for set view
{
	return m_Marco.getCurrPos();
}

int Board::getMoneyStatus() const
{
	return m_Marco.getMoney();
}

bool Board::readBoardFromFile(const std::string level)
{
	std::ifstream myfile;
	myfile.open(level);

	if (!myfile.is_open())
		throw std::exception("Cannot open file\n");

	if (!(myfile >> m_rowSize >> m_colSize)) //if there is no more levels - return false;
		return false;

	myfile.get(); //"eat" the \n

	for (int ROWS = 0; ROWS < m_rowSize; ROWS++)
	{
		for (int COLS = 0; COLS < m_colSize; COLS++)
		{
			//set object position
			sf::Vector2f pos(float(COLS * Utilities::SIZE_OF_PIC), float(ROWS * Utilities::SIZE_OF_PIC));

			char c;
			myfile.get(c);

			switch (c)
			{
			case UtilitiesChar::C_MARCO:
				m_Marco.setStart(pos, ToolBar::instance().getPicture(c));
				m_Marco.setCurrPos(pos);
				break;

			case UtilitiesChar::C_KOFIFO:
				m_Kofifo.setStart(pos, ToolBar::instance().getPicture(c));
				m_Kofifo.setCurrPos(pos);
				break;

			case UtilitiesChar::C_OWNER:
				m_Owners.push_back(std::make_unique<Owner>());
				m_Owners[m_Owners.size() - 1]->setStart(pos, ToolBar::instance().getPicture(c));
				m_Owners[m_Owners.size() - 1]->setCurrPos(pos);
				break;

			case UtilitiesChar::C_WALL:
				m_staticObject.push_back(std::make_unique<Wall>(pos, ToolBar::instance().getPicture(c))); break;

			case UtilitiesChar::C_WEAPON:
				m_staticObject.push_back(std::make_unique<Weapon>(pos, ToolBar::instance().getPicture(c))); break;

			case UtilitiesChar::C_FOOD:
				m_staticObject.push_back(std::make_unique<Food>(pos, ToolBar::instance().getPicture(c))); break;

			case UtilitiesChar::C_MONEY:
				m_staticObject.push_back(std::make_unique<Money>(pos, ToolBar::instance().getPicture(c))); break;

			case UtilitiesChar::C_TREASURE:
				m_staticObject.push_back(std::make_unique<Treasure>(pos, ToolBar::instance().getPicture(c)));
				m_Marco.setTreasureKey(1);
				break;

			case UtilitiesChar::C_GIFT:
			{
				auto n = rand() % 3;

				if (n == 0)
					m_staticObject.push_back(std::make_unique<MoneyGift>(pos, ToolBar::instance().getPicture(c)));
				else if (n == 1)
					m_staticObject.push_back(std::make_unique<WeaponGift>(pos, ToolBar::instance().getPicture(c)));
				else
					m_staticObject.push_back(std::make_unique<LifeGift>(pos, ToolBar::instance().getPicture(c)));

				break;
			}
			case UtilitiesChar::C_DOOR:
				m_staticObject.push_back(std::make_unique<Door>(pos, ToolBar::instance().getPicture(c))); break;
				break;

			case UtilitiesChar::C_BOSS:
				m_Boss.setStart(pos, ToolBar::instance().getPicture(c));
				m_Boss.setCurrPos(pos);
				m_Boss.setHP(Life::LIFE_OF_BOSS);
				m_Boss.setExist(true);
				break;

			case ' ':
				pos.x += Utilities::SIZE_OF_PIC;
				pos.y += Utilities::SIZE_OF_PIC;
				m_FreePlaces.push_back(pos);
				break;

			default: continue;
			}

		}
		myfile.get();
	}
	myfile.get();

	myfile.close();
	return true;
}

void Board::useBoost(const Boosts boostStruct)
{
	short numOfChoice = 0;
	if (boostStruct.HP) {
		m_Marco.setHP(20);
		numOfChoice++;
	}

	if(boostStruct.marcoSpeed) {
		m_Marco.setSpeed(m_Marco.getSpeed() + 150);
		numOfChoice++;
	}

	if (boostStruct.kofifoSpeed) {
		m_Kofifo.setSpeed(m_Kofifo.getSpeed() + 50);
		numOfChoice++;
	}

	if(boostStruct.bombs) {
		m_Marco.setBombsCapacity(2);
		numOfChoice++;
	}

	if(boostStruct.teleports) {
		m_Marco.setTrans(3);
		numOfChoice++;
	}

	m_Marco.setMoney(-numOfChoice * Utilities::BOOST_COST);
}

void Board::dealWithSound(Sounds i)
{
	m_Sound.setBuffer(SoundEffects::instance().getSound(int(i)));
	m_Sound.play();
}