#include "Object.h"

Object::Object(sf::Vector2f pos, sf::Sprite spr) : m_StartPos(pos)
{
	m_Sprite = spr;
	m_Sprite.setOrigin(sf::Vector2f(m_Sprite.getTextureRect().width / 2.f, m_Sprite.getTextureRect().height / 2.f));
	m_Sprite.setPosition(m_Sprite.getOrigin().x + pos.x, m_Sprite.getOrigin().y + pos.y);
}

void Object::setStart(sf::Vector2f& pos, sf::Sprite spr)
{
	m_StartPos = pos;
	m_Sprite = spr;
	m_Sprite.setOrigin(sf::Vector2f(m_Sprite.getTextureRect().width / 2.f, m_Sprite.getTextureRect().height / 2.f));
	m_Sprite.setPosition(m_Sprite.getOrigin().x + pos.x, m_Sprite.getOrigin().y + pos.y);
}

sf::Vector2f Object::getStartPos() const
{
	return m_StartPos;
}

sf::Sprite& Object::getSprite()
{
	return m_Sprite;
}

void Object::draw(sf::RenderWindow& window) const
{
	window.draw(m_Sprite);
}

bool Object::getExist() const
{
	return m_exist;
}

void Object::setExist(bool a)
{
	m_exist = a;
}

sf::IntRect Object::getTextureRect()
{
	return this->getSprite().getTextureRect();
}

