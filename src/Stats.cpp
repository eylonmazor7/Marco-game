#include "Stats.h"

Stats& Stats::instance()
{
	static auto instance = Stats();
	return instance;
}

Stats::Stats()
{
	if (!m_font.loadFromFile("arial.ttf"))
		throw std::exception("Cant find arial.ttf\n");

	if (!m_tex.loadFromFile("toolbar1.png"))
		throw std::exception("Cannot open picture \n");
	
	m_rec.setSize(sf::Vector2f(Utilities::WINDOW_SIZE_WITDH, 270.f));
	m_rec.setTexture(&m_tex);
	m_rec.setPosition(0.f, 0.f);
	m_view.reset({ 0.f, 0.f, (float)Utilities::WINDOW_SIZE_WITDH ,  (float)(Utilities::WINDOW_SIZE_HEIGHT * 0.318) });
	m_view.setViewport({ 0.f, 0.682f, 1.f, 0.318f });

	initializeText();
}

std::string Stats::convertIntToString(int i) //convert int to text 
{
	std::stringstream itos;
	itos << i;
	return itos.str();
}

void Stats::initializeText()
{
	m_details.resize(Utilities::TOOLBAR_DATA);
	for (int i = 0; i < Utilities::TOOLBAR_DATA; i++)
	{
		m_details[i].setFont(m_font);
		m_details[i].setCharacterSize(Utilities::CHAR_SIZE);
		m_details[i].setFillColor(sf::Color::Black);
	}

	m_details[static_cast<int>(textEnum::treasure)].setPosition(85.f, 5.f);
	m_details[static_cast<int>(textEnum::HP)].setPosition(220.f, 80.f);
	m_details[static_cast<int>(textEnum::Bombs)].setPosition(550.f, 60.f);
	m_details[static_cast<int>(textEnum::Money)].setPosition(920.f, 75.f);
	m_details[static_cast<int>(textEnum::Level)].setPosition(600.f, 125.f);
	m_details[static_cast<int>(textEnum::Food)].setPosition(230.f, 200.f);
	m_details[static_cast<int>(textEnum::Ammo)].setPosition(550.f, 215.f);
	m_details[static_cast<int>(textEnum::Tele)].setPosition(910.f, 195.f);
}

void Stats::setViewAndPrint(sf::RenderWindow& window, struct Details& d)
{
	window.setView(m_view);
	window.draw(m_rec);

	m_details[static_cast<int>(textEnum::treasure)].setString(convertIntToString(d.keys));
	m_details[static_cast<int>(textEnum::HP)].setString(convertIntToString(d.HP));
	m_details[static_cast<int>(textEnum::Bombs)].setString(convertIntToString(d.bomb));
	m_details[static_cast<int>(textEnum::Money)].setString(convertIntToString(d.money));
	m_details[static_cast<int>(textEnum::Level)].setString(convertIntToString(d.level));
	m_details[static_cast<int>(textEnum::Food)].setString(convertIntToString(d.food));
	m_details[static_cast<int>(textEnum::Ammo)].setString(convertIntToString(d.ammo));
	m_details[static_cast<int>(textEnum::Tele)].setString(convertIntToString(d.tele));
	
	for(int i = 0 ; i < Utilities::TOOLBAR_DATA ; i++)
		window.draw(m_details[i]);
}
