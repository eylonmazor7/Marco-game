#include "BossBullet.h"

BossBullet::BossBullet(sf::Vector2f pos, sf::Sprite spr, sf::Vector2f dir) : Bullet(pos, spr, dir)
{
	m_currPosition = this->getSprite().getPosition();
}

sf::Vector2f BossBullet::getCurr() const
{
	return m_currPosition;
}

void BossBullet::bossFire()
{
	this->getSprite().move(this->getDir());
	m_currPosition = this->getSprite().getPosition();
}