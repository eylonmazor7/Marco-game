#pragma once
#include "Bomb.h"

float Bomb::m_end = 280;

Bomb::Bomb(sf::Vector2f pos, sf::Sprite spr) : Object(pos, spr)
{
	m_timer.restart();
	m_clockForAnimation.restart();
	m_Circle.setRadius(Weapons::BOMB_RADIUS);
	m_Circle.setFillColor(sf::Color(255, 255, 255, 128));
	m_Circle.setPosition(this->getSprite().getPosition().x - (float)Weapons::BOMB_RADIUS,
		this->getSprite().getPosition().y - (float)Weapons::BOMB_RADIUS);
}

bool Bomb::timeToBlow() const
{
	return (m_timer.getElapsedTime().asSeconds() >= 3.0f);
}

void Bomb::blow()
{
	if (m_clockForAnimation.getElapsedTime().asSeconds() > 0.1f)
	{
		sf::IntRect ir = this->getTextureRect();
		if (this->getTextureRect().left >= m_end)
		{
			m_timer.restart();
			this->setExist(false);
		}

		else
		{
			ir.left += 41;
			this->getSprite().setTextureRect(ir);
		}

		this->getSprite().setTextureRect(this->getTextureRect());
		m_clockForAnimation.restart();
	}
}

sf::CircleShape& Bomb::getCir()
{
	return m_Circle;
}
