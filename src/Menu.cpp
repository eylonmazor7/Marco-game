#include "Menu.h"
#include <Windows.h>

Menu::Menu()
{
	if (!m_font.loadFromFile("Destacy.ttf"))
		throw std::exception("Cant find Destacy.ttf\n");
	m_menuOptions.resize(Utilities::MENU_SIZE);
	m_texts.resize(Utilities::MENU_SIZE);
	for (int i = 0; i < Utilities::MENU_SIZE; i++)
	{
		m_menuOptions[i].setFillColor(sf::Color::Transparent);
		m_menuOptions[i].setSize(sf::Vector2f(210, 50));
		m_menuOptions[i].setOutlineColor(sf::Color::White);
		m_menuOptions[i].setOutlineThickness(5);
		m_texts[i].setString(m_names[i]);
		m_texts[i].setFont(m_font);
		m_texts[i].setFillColor(sf::Color::Black);
	}
	createMenu();
}

void Menu::createMenu()
{
	bg.loadFromFile("menuPic.png");
	bg.setSmooth(true);
	bgPic.setTexture(&bg);
	for (int i = 0; i < Utilities::MENU_SIZE; i++)
	{
		switch (i)
		{
		case 0:
			m_menuOptions[i].setPosition(108, 470);
			m_texts[i].setPosition(190, 475);
			break;

		case 1:
			m_menuOptions[i].setPosition(340, 470);
			m_texts[i].setPosition(390, 475);
			break;

		case 2:
			m_menuOptions[i].setPosition(572, 470);
			m_texts[i].setPosition(652, 475);
			break;
		default:
			break;
		}
	}
}

bool Menu::startGameMenu(sf::RenderWindow& window) //main menu
{
	while (window.isOpen())
	{
		window.clear();
		drawMenu(window);
		window.display();

		for (auto event = sf::Event{}; window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				for (int i = 0; i < Utilities::MENU_SIZE; i++)
					if (isMouseOverIcon(window, i))
						switch (menuAction(window, i))
						{
						case Choice::E_exitGame:
							window.close();
							return false;
							break;
						case Choice::E_startGame:
							return true;
							break;
						
						case Choice::E_instructions:
							showInstructions(window);
							break;
						}
				break;
			case sf::Event::Closed:
				window.close();
				return false;
				break;
			}
			for (int i = 0; i < Utilities::MENU_SIZE; i++)
				if (isMouseOverIcon(window, i))
					m_menuOptions[i].setOutlineColor(sf::Color::Blue);
				else
					m_menuOptions[i].setOutlineColor(sf::Color::White);
		}
	}
	return true;
}

void Menu::drawMenu(sf::RenderWindow& window)
{
	bgPic.setSize(sf::Vector2f(900, 600));
	window.draw(bgPic);

	for (int i = 0; i < Utilities::MENU_SIZE; i++)
	{
		window.draw(m_menuOptions[i]);
		window.draw(m_texts[i]);
	}
}

bool Menu::isMouseOverIcon(sf::RenderWindow& window, int index) //level pressed
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(210, 50));
	shape.setPosition(float(108 + index * 232), 470);

	auto shapePos = shape.getGlobalBounds();

	if (shapePos.contains(float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y)))
		return true;
	return false;
}

const Choice Menu::menuAction(sf::RenderWindow& window, int index)
{
	switch (index)
	{
	case 0:
		return Choice::E_exitGame;
		break;

	case 1:
		return Choice::E_startGame;
		break;

	case 2:
		return Choice::E_instructions;
		break;

	default:
		return Choice::E_exitGame;
		break;
	}
}

void Menu::showInstructions(sf::RenderWindow& window)
{
	sf::CircleShape cir((float)window.getSize().x);
	cir.setRadius(window.getSize().y / 2.f);
	cir.setOutlineThickness(3);

	if (!m_font.loadFromFile("arial.ttf"))
		throw std::exception("Cant find arial.ttf\n");

	sf::Text help;
	sf::Text headline;
	headline.setFont(m_font);
	headline.setCharacterSize((unsigned)19);
	headline.setFillColor(sf::Color::Black);
	headline.setColor(sf::Color::White);
	headline.setOutlineThickness(2);
	headline.setOutlineColor(sf::Color::Red);
	headline.setPosition(120, 80);

	help.setFont(m_font);
	help.setLineSpacing(1.5);
	help.setCharacterSize((unsigned)19);
	help.setFillColor(sf::Color::Black);
	help.setColor(sf::Color::White);
	help.setOutlineThickness(2);
	help.setOutlineColor(sf::Color::Blue);
	help.setPosition(70, 120);

	std::string str("Purpose of the game: Reach Marco's mother.\n");
	str += "All keys must be collected to go through one level.\n";
	str += "Only go through the door for next level.\n";
	str += "Monsters and Bullets must be avoided.\n";
	str += "You can change fire shots by choosing 1/2/3.\n";
	str += "Buttons: Moving- W, A, D, S\n";
	str += "E - Bomb,\n";
	str += "Z - Teleport,\n";
	str += "Mouse left click - Shooting.\n";
	str += "\n";
	str += "Click anywhere inside circle to continue\n";

	std::string str1("Food - use to feed Kofifo when it reaches Marco.\n");
	str1 += "If Marco is out of food, Kofife will steal random\n";
	str1 += "resources from Marco.\n";
	str1 += "Money - used to buy boosts after each stage, make\n";
	str1 += "sure you collect the money bags.\n";
	str1 += "Teleporting will change your position instantly & randomly.\n";
	str1 += "Keep in mind that you can buy only one of each boost.\n";
	str1 += "Pay attention for the boss monster in the last stage.\n";
	str1 += "The boss is very powerful, it can fly above walls\n";
	str1 += "and can shoot fire through them.\n";
	str1 += "Click anywhere inside circle to continue, \n";
	str1 += "                             GOOD LUCK!\n";
	str1 += "         Dor Rozin, Tal Museri and Eylon Mazor";

	std::string head1("                 Instructions:");
	std::string head2("                 Rules and Tips:");

	std::vector<std::string> helpVec, headlines;
	helpVec.push_back(str);
	helpVec.push_back(str1);
	headlines.push_back(head1);
	headlines.push_back(head2);

	for (int i = 0; i < helpVec.size(); i++)
	{
		window.draw(bgPic);
		help.setString(helpVec[i]);
		headline.setString(headlines[i]);
		window.draw(cir);
		window.draw(help);
		window.draw(headline);
		window.display();

		bool clicked = false;

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::MouseButtonPressed:
					auto mousePos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
					if (cir.getGlobalBounds().contains(mousePos))
						clicked = true;
					break;
				}
			}
			if (clicked)
				break;
		}
		window.clear();

	}

	if (!m_font.loadFromFile("Destacy.ttf"))
		throw std::exception("Cant find Destacy.ttf\n");
}