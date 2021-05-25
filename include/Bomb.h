#pragma once

#include "Object.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Utilities.h>

class Bomb : public Object
{
public:
	Bomb(sf::Vector2f, sf::Sprite);
	virtual ~Bomb() = default;

	bool timeToBlow() const;
	void blow();
	sf::CircleShape& getCir();

private:
	static float m_end;
	sf::Clock m_timer;
	sf::Clock m_clockForAnimation;
	sf::CircleShape m_Circle;
};