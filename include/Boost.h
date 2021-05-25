#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Utilities.h"

class Boost
{
public:
	Boost();
	~Boost() = default;
	void printBoost(sf::RenderWindow&, Boosts&, int);
	
private:
	std::string convertIntToString(int);
	void drawBoosts(sf::RenderWindow&, int);
	bool isMouseOverBoost(sf::RenderWindow&, int);
	void boostAction(sf::RenderWindow&, Boosts&,int, int&);
	bool isMouseOverBackButton(sf::RenderWindow&);

	bool m_ret = false;
	std::vector <sf::Texture> m_boostPics;
	std::vector <sf::RectangleShape> m_boostVec;
	sf::Texture m_levelUpPic;
	sf::Texture m_levelUpBgPic;
	sf::RectangleShape m_levelUpRec;
	sf::RectangleShape m_levelUpBgRec;
	sf::Font m_font;
	sf::Text m_text;
	sf::Texture m_backTex;
	sf::RectangleShape m_backRec;
	static float m_boostSize; 
	static unsigned int m_moneyTextSize;
	static float m_boostGap;
	static float m_boostHeight;
	static sf::Vector2f m_bgSize;
	static sf::Vector2f m_backSize;
};