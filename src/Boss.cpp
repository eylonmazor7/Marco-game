#include "Boss.h"

Boss::Boss()
{
	this->setExist(false);
	this->setSpeed(Speed::BOSS_SPEED);
}

sf::Vector2f Boss::setDirection(float deltaTime, sf::Vector2f& dirToMarco)
{
	return this->chaseAfterMarco(deltaTime, dirToMarco);
}