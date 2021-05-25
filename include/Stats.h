#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include <sstream>
#include "Utilities.h"

class Stats
{
public:
	static Stats& instance();
	~Stats() = default;

	void setViewAndPrint(sf::RenderWindow&, struct Details&);

private:
	void initializeText();
	std::string convertIntToString(int);
	
	Stats();
	Stats(const Stats&) = delete;
	Stats& operator= (const Stats&) = delete;
	sf::Font m_font;
	sf::Texture m_tex;
	sf::RectangleShape m_rec;
	sf::View m_view;
	std::vector <sf::Text> m_details;
};