#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Menu
{
public:
	Menu();
	~Menu() = default;

	bool startGameMenu(sf::RenderWindow&);

private:
	void drawMenu(sf::RenderWindow&);
	void createMenu();
	bool isMouseOverIcon(sf::RenderWindow&, int);
	const Choice menuAction(sf::RenderWindow&, int);
	void showInstructions(sf::RenderWindow&);

	sf::RectangleShape bgPic;
	sf::Texture bg;
	std::vector <sf::RectangleShape> m_menuOptions;
	std::vector <sf::Text> m_texts;
	std::vector <std::string> m_names{ "Quit", "Find Mom", "Help" };
	sf::Font m_font;
};
