#include "Owner.h"

Owner::Owner()
{
	this->setSpeed(Speed::OWNER_SPEED);
}

sf::Vector2f Owner::setDirection(float deltaTime, sf::Vector2f& dirToMarco)
{
	return this->chaseAfterMarco(deltaTime, dirToMarco);
}

int Owner::getHP()
{
	return m_life;
}

void Owner::setHP(int a)
{
	m_life += a;
	if (m_life <= 0)
		this->setExist(false);
}