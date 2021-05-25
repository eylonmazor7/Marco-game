#pragma once
#include"MobileObject.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>

class Kofifo : public MobileObject
{
public:
	Kofifo();
	virtual ~Kofifo() = default;

	virtual sf::Vector2f setDirection(float, sf::Vector2f&) override;
	void changePos(bool);
	bool getChangePos();

private:
	bool m_changePos = false;
};