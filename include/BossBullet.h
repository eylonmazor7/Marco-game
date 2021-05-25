#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>

class BossBullet : public Bullet
{
public:
	BossBullet(sf::Vector2f, sf::Sprite, sf::Vector2f);
	virtual ~BossBullet() = default;
	
	sf::Vector2f getCurr() const;
	
	void bossFire();
	
private:
	sf::Vector2f m_currPosition;
};