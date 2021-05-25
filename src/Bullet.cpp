#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos , sf::Sprite spr, sf::Vector2f dir) : Object(pos, spr) , m_direction(dir)
{	
}

void Bullet::fire()
{
	this->getSprite().move(m_direction);
}

sf::Vector2f Bullet::getDir()
{
	return m_direction;
}