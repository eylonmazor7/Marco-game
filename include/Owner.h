#pragma once
#include"MobileObject.h"
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Owner : public MobileObject
{
public:
	Owner();
	virtual ~Owner() = default;
	int getHP();
	void setHP(int);
	virtual sf::Vector2f setDirection(float, sf::Vector2f&) override;

private:
	int m_life = Life::LIFE_OF_OWNER;
};