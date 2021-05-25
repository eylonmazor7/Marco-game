#pragma once
#include "Teleport.h"

Teleport::Teleport(sf::Vector2f pos, sf::Sprite spr) : Object(pos, spr)
{
	m_clockForAnimation.restart();
}

void Teleport::transform()
{
	sf::IntRect ir = this->getTextureRect();
	if (this->getTextureRect().left == 150)
	{
		this->setExist(false);
	}

	else
	{
		ir.left += 50;
		this->getSprite().setTextureRect(ir);
	}

	this->getSprite().setTextureRect(this->getTextureRect());
	m_clockForAnimation.restart();
}
