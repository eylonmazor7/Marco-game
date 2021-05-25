#include "Boost.h"
#include "Utilities.h"

float Boost::m_boostGap = 160;
float Boost::m_boostHeight = 450;
unsigned int Boost::m_moneyTextSize = 50;
float Boost::m_boostSize = 100;
sf::Vector2f Boost::m_bgSize = sf::Vector2f(1100.f, 800.f);
sf::Vector2f Boost::m_backSize = sf::Vector2f(70.f, 70.f);

Boost::Boost()
{
	m_boostPics.resize(Utilities::BOOST_NUM);
	m_boostVec.resize(Utilities::BOOST_NUM);

	for (int i = 0; i < Utilities::BOOST_NUM; i++)
	{
		switch (i)
		{
		case 0:
			m_boostPics[i].loadFromFile("lifeBoost.png");
			break;

		case 1:
			m_boostPics[i].loadFromFile("speed.png");
			break;

		case 2:
			m_boostPics[i].loadFromFile("kofifoSpeedBoost.png");
			break;

		case 3:
			m_boostPics[i].loadFromFile("bombBoost.png");
			break;

		case 4:
			m_boostPics[i].loadFromFile("transBoost.png");
			break;

		default:
			break;
		}
		m_boostPics[i].setSmooth(true);
		m_boostVec[i].setTexture(&m_boostPics[i]);
		m_boostVec[i].setSize(sf::Vector2f(m_boostSize, m_boostSize));
	}

	m_levelUpBgPic.loadFromFile("boostMenu.png");
	m_levelUpBgPic.setSmooth(true);
	m_levelUpBgRec.setTexture(&m_levelUpBgPic);
	m_levelUpBgRec.setSize(m_bgSize);

	m_font.loadFromFile("Destacy.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(m_moneyTextSize);
	m_text.setPosition(525.f, 630.f);
	m_text.setFillColor(sf::Color::Blue);
	m_text.Bold;

	m_backTex.loadFromFile("back.png");
	m_backTex.setSmooth(true);
	m_backRec.setTexture(&m_backTex);
	m_backRec.setSize(m_backSize);
	m_backRec.setPosition(650.f, 630.f);
}

void Boost::printBoost(sf::RenderWindow& window, Boosts& choosenBoost,int money)
{
	window.create(sf::VideoMode(Utilities::WINDOW_SIZE_WITDH, Utilities::WINDOW_SIZE_HEIGHT - 50), "Play Marco", sf::Style::Close);

	while (window.isOpen())
	{
		window.clear();
		drawBoosts(window, money);
		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				for (int i = 0; i < Utilities::BOOST_NUM; i++)
				{
					if (isMouseOverBoost(window, i))
					{
						boostAction(window, choosenBoost, i, money);
						break;
					}
					else if (isMouseOverBackButton(window))
						m_ret = true;
				}
				break;
			}
		}
		if (m_ret)
		{
			m_ret = false;
			return;
		}
	}
}

void Boost::drawBoosts(sf::RenderWindow& window, int money)
{
	window.draw(m_levelUpBgRec);

	for (int i = 0; i < Utilities::BOOST_NUM; i++)
	{
		m_boostVec[i].setPosition(m_boostGap * (i + 1), m_boostHeight);
		window.draw(m_boostVec[i]);
	}

	auto str = convertIntToString(money);
	m_text.setString(str);
	window.draw(m_text);
	window.draw(m_backRec);
}

bool Boost::isMouseOverBoost(sf::RenderWindow& window, int i)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_boostSize, m_boostSize));
	shape.setPosition(m_boostGap * (i + 1), m_boostHeight);

	auto shapePos = shape.getGlobalBounds();

	if (shapePos.contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y))
		return true;
	return false;
}

void Boost::boostAction(sf::RenderWindow& window, Boosts& choosenBoost, int i, int& money)
{
	if (money < Utilities::BOOST_COST)
		return;

	switch (i)
	{
	case 0:
		if (choosenBoost.HP) return;
		choosenBoost.HP = true;
		break;

	case 1:
		if (choosenBoost.marcoSpeed) return;
		choosenBoost.marcoSpeed = true;
		break;

	case 2:
		if (choosenBoost.kofifoSpeed) return;
		choosenBoost.kofifoSpeed = true;
		break;

	case 3:
		if (choosenBoost.bombs) return;
		choosenBoost.bombs = true;
		break;

	case 4:
		if (choosenBoost.teleports) return;
		choosenBoost.teleports = true;
		break;

	default:
		return;
	}
	money -= Utilities::BOOST_COST;
}

std::string Boost::convertIntToString(int i) //convert int to text 
{
	std::stringstream itos;
	itos << i;
	return itos.str();
}

bool Boost::isMouseOverBackButton(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setSize(m_backSize);
	shape.setPosition(650.f , 630.f);

	auto shapePos = shape.getGlobalBounds();

	if (shapePos.contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y))
		return true;
	return false;
}