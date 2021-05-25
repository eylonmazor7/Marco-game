#include "Kofifo.h"

Kofifo::Kofifo()
{
	this->setSpeed(Speed::KOFIFO_SPEED);
}

sf::Vector2f Kofifo::setDirection(float deltaTime, sf::Vector2f& dirToMarco)
{
	return this->chaseAfterMarco(deltaTime, dirToMarco);
}

void Kofifo::changePos(bool a)
{
	m_changePos = a;
}

bool Kofifo::getChangePos()
{
	return m_changePos;
}
