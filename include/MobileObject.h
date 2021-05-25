#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>

class MobileObject : public Object
{
public:
	MobileObject() { }
	MobileObject(sf::Vector2f, sf::Sprite);
	virtual ~MobileObject() = default;
	
	sf::Vector2f getDirection() const;
	sf::Vector2f getCurrPos() const;
	
	void setCurrPos(sf::Vector2f&);
	virtual sf::Vector2f setDirection(float, sf::Vector2f&) = 0;

	void startAnimation(int, int);
	sf::Vector2f chaseAfterMarco(float, sf::Vector2f&) ; 
	
	void moveObject(const float dt, sf::Vector2f& dirToMarco);
	void moveBack();

	void setSpeed(const float);
	float getSpeed() const;
	
private:
	sf::Clock m_clockForAnimation;
	sf::Vector2f m_currPos;
	sf::Vector2f m_direction;
	float m_speed = 0;
};
