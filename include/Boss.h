#pragma once

#include"Owner.h"
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Boss : public Owner
{
public:
	Boss();
	virtual ~Boss() = default;
	virtual sf::Vector2f setDirection(float, sf::Vector2f&) override;
};