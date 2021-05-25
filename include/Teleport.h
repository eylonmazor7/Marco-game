#pragma once

#include "Object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Teleport : public Object 
{
public:
	Teleport(sf::Vector2f, sf::Sprite);
	virtual ~Teleport() = default;

	void transform();

private:
	sf::Clock m_clockForAnimation;
};