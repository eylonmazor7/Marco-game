#include "MobileObject.h"

MobileObject::MobileObject (sf::Vector2f pos, sf::Sprite spr) : Object(pos, spr)
{
	m_currPos = pos;
}

sf::Vector2f MobileObject::getCurrPos() const
{
	return m_currPos;
}

void MobileObject::setCurrPos(sf::Vector2f& pos)
{
	m_currPos = pos;
	this->getSprite().setPosition(pos);
}

void MobileObject::startAnimation(int startLeft, int endLeft)
{
	if (m_clockForAnimation.getElapsedTime().asSeconds() > 0.1f)
	{
		sf::IntRect ir = this->getTextureRect();
		if (this->getTextureRect().left >= endLeft)
		{
			ir.left = 0;
			this->getSprite().setTextureRect(ir);
		}

		else
		{
			ir.left += startLeft;
			this->getSprite().setTextureRect(ir);
		}

		this->getSprite().setTextureRect(this->getTextureRect());
		m_clockForAnimation.restart();
	}
}

sf::Vector2f MobileObject::chaseAfterMarco(float deltaTime, sf::Vector2f& dirToMarco)
{
	sf::IntRect ir(0, 0, 37, 50);
	int choice = 0;
	dirToMarco.x *= (m_speed * deltaTime);
	dirToMarco.y *= (m_speed * deltaTime);
	float x = dirToMarco.x;
	float y = dirToMarco.y;

	//0 -> left, 1 -> right, 2 -> up, 3 -> down
	if (x < 0 && y < 0)
		if (abs(x) > abs(y))
			choice = 0;
		else
			choice = 2;
	else if (x < 0 && y > 0)
		if (abs(x) > y)
			choice = 0;
		else
			choice = 3;
	else if (x > 0 && y < 0)
		if (x > abs(y))
			choice = 1;
		else
			choice = 2;
	else
		if (x > y)
			choice = 1;
		else
			choice = 3;

	//animation move algorithm
	if (choice == 1) // right
	{
		ir.top = 100;
		this->getSprite().setTextureRect(ir);
	}
	else if (choice == 0) // left
	{
		ir.top = 50;
		this->getSprite().setTextureRect(ir);
	}
	else if (choice == 3) //down
	{
		ir.top = 0;
		this->getSprite().setTextureRect(ir);
	}
	else if (choice == 2) // up
	{
		ir.top = 150;
		this->getSprite().setTextureRect(ir);
	}

	return dirToMarco;
}

void MobileObject::moveObject(const float dt, sf::Vector2f& dirToMarco)
{
	m_direction = this->setDirection(dt, dirToMarco);
	this->getSprite().move(m_direction);
	m_currPos = this->getSprite().getPosition();
};

void MobileObject::moveBack()
{
	m_direction.x *= -1; 
	m_direction.y *= -1;
	this->getSprite().move(m_direction);
	m_currPos = this->getSprite().getPosition();
}

sf::Vector2f MobileObject::getDirection() const
{
	return m_direction;
}

void MobileObject::setSpeed(const float speed)
{
	m_speed = speed;
}

float MobileObject::getSpeed() const
{
	return m_speed;
}