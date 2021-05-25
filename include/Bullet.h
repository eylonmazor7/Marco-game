#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class Bullet : public Object
{
public:
	Bullet(sf::Vector2f, sf::Sprite, sf::Vector2f);
	virtual ~Bullet() = default;
	sf::Vector2f getDir();

	void fire();

private:
	sf::Vector2f m_direction;
};