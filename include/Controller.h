#pragma once
#include "Board.h"
#include "Stats.h"
#include "Toolbar.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Controller
{ 
public:
	Controller();
	~Controller() = default;

	bool startGame();

private:

	void game();
	void setCenter();
	void chooseGun(const sf::Event);
	void startAni();
	void stopAndDisplay(const std::string);
	bool run(const short);
	bool m_Fail = false;
	std::vector<std::string> m_levels;

	sf::Texture m_tex;
	sf::Sprite m_bgPic;
	sf::Music m_music;
	sf::Clock m_deltaTime;
	sf::Clock m_gameClock;
	sf::Clock m_clockForMom;
	sf::Clock m_clockForstartAni;
	sf::Time m_gameTime;
	sf::View m_view;
	sf::RenderWindow m_window;

	bool m_running = true;
	Boost m_boost;
	Board m_Board;
	Menu m_menu;
	Details m_details;
};