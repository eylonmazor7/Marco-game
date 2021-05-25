#include "Marco.h"
#include <iostream>
#include <cmath>

Marco::Marco()
{
	this->setSpeed(Speed::MARCO_SPEED);
}

sf::Vector2f Marco::setDirection(float dt, sf::Vector2f& dirToMarco)
{
	sf::Vector2f movement(0.0f, 0.0f);
	sf::IntRect ir(0, 0, 50, 31);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movement.y -= this->getSpeed() * dt;
		ir.top = 31;
		this->getSprite().setTextureRect(ir);
		LastDirection = movement;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movement.y += this->getSpeed() * dt;
		ir.top = 0;
		this->getSprite().setTextureRect(ir);
		LastDirection = movement;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movement.x -= this->getSpeed() * dt;
		ir.top = 93;
		this->getSprite().setTextureRect(ir);
		LastDirection = movement;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movement.x += this->getSpeed() * dt;
		ir.top = 62;
		this->getSprite().setTextureRect(ir);
		LastDirection = movement;
	}

	return movement;
}

void Marco::marcoKofifoCol()
{
	bool temp = false; //if marco have a food for kofifo
	bool found = true;

	if (m_food)
	{
		m_food--;
		temp = true;
	}

	while (found)
	{
		switch (rand() % 5)
		{
		case 0:
			if (m_BombCapacity <= 0) continue;
			temp ? m_BombCapacity++ : m_BombCapacity--;
			break;
		case 1:
			if (m_booletCapacity <= 0) continue;
			temp ? m_booletCapacity += Utilities::KOFIFO_PRIZE : m_booletCapacity -= Utilities::KOFIFO_PRIZE;
			if (m_booletCapacity < 0) m_booletCapacity = 0;
			break;
		case 2:
			if (m_money <= 0) continue;
			temp ? m_money += Utilities::KOFIFO_PRIZE : m_money -= Utilities::KOFIFO_PRIZE;
			if (m_money < 0) m_money = 0;
			break;
		case 3:
			if (m_transTimes <= 0) continue;
			temp ? m_transTimes += (int)floor(Utilities::KOFIFO_PRIZE*0.3) : m_transTimes -= (int)floor(Utilities::KOFIFO_PRIZE*0.3);
			if (m_transTimes < 0) m_transTimes = 0;
			break;
		case 4:
			temp ? m_life += Utilities::KOFIFO_PRIZE : m_life -= Utilities::KOFIFO_PRIZE;
			if (m_life < 0) m_life = 0;
			break;
		}
		found = false;
	}
}

int Marco::getFood() const
{
	return m_food;
}

void Marco::setFood(int num)
{
	m_food += num;
}

int Marco::getHP() const
{
	return m_life;
}

void Marco::setHP(int num)
{
	m_life += num;
}

void Marco::setReady(bool a)
{
	m_readyToNext = a;
}

int Marco::getReady() const
{
	return m_readyToNext;
}

sf::Vector2f Marco::getLastDirection()
{
	return LastDirection;
}

int Marco::getBulletsCapacity() const
{
	return m_booletCapacity;
}

int Marco::getBombsCapacity() const
{
	return m_BombCapacity;
}

int Marco::getTransTimes() const
{
	return m_transTimes;
}

void Marco::setBulletsCapacity(int num)
{
	m_booletCapacity += num;
}

void Marco::setBombsCapacity(int num)
{
	m_BombCapacity += num;
}

void Marco::setTreasureKey(int num)
{
	m_TreasureKey += num;
}

void Marco::restartKeys()
{
	m_TreasureKey = 0;
	m_readyToNext = false;
}

int Marco::getTreasureKey() const
{
	return m_TreasureKey;
}

void Marco::checkDoorKeyTerms()
{
	if (!m_TreasureKey)
		m_readyToNext = true;
	else
		this->moveBack();
}

void Marco::setTrans(int trans)
{
	m_transTimes += trans;
}

void Marco::setDetails()
{
	m_booletCapacity = Weapons::BULLETS_CAPA;
	m_BombCapacity = Weapons::BOMB_CAPA;
	m_transTimes = Utilities::MARCO_TRANS_TIMES;
	m_life = Life::LIFE_OF_MARCO;
	m_food = Utilities::MARCO_FOOD;
	m_TreasureKey = 0;
	m_money = 0;
}

void Marco::setMoney(int num)
{
	m_money += num;
}

int Marco::getMoney() const
{
	return m_money;
}