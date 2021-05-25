#include "Controller.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Windows.h"
#include <fstream>

Controller::Controller()
{
	std::ifstream myfile;
	std::string buff;
	myfile.open("levels.txt");
	while (myfile >> buff)
		m_levels.push_back(buff);
	
	myfile.close();
	
	if (!m_tex.loadFromFile("bg.png"))
		throw std::exception("Cant find bg.png\n");

	m_tex.setSmooth(true);
	m_bgPic.setTexture(m_tex);
	m_bgPic.setColor(sf::Color(255, 255, 255, 128));
	
	m_music.openFromFile("startSong.ogg");
	m_music.play();
	m_music.setLoop(true);
}

bool Controller::startGame()
{
	m_Board.cleanDetails(true);
	m_view.reset({ 0.f, 0.f, Utilities::WINDOW_SIZE_WITDH,  Utilities::WINDOW_SIZE_HEIGHT });
	m_view.setViewport({ 0.f, 0.f, 1.f, 0.682f });
	m_window.create(sf::VideoMode(900, 600), "Play Marco", sf::Style::Close);

	if (m_menu.startGameMenu(m_window))
	{
		m_music.setVolume(50);
		for (int i = 0; i < m_levels.size(); i++) //loop of levels
		{
			m_view.reset({ 0.f, 0.f, Utilities::WINDOW_SIZE_WITDH,  Utilities::WINDOW_SIZE_HEIGHT });
			m_window.create(sf::VideoMode(Utilities::WINDOW_SIZE_WITDH, Utilities::WINDOW_SIZE_HEIGHT), "Play Marco", sf::Style::Close);
			m_details.level = i + 1;

			if (i == 0)
				startAni(); // for the first level only

			if (run(i))
			{
				if (i != m_levels.size() - 1) //if its not the last level
				{
					m_Board.dealWithSound(Sounds::levelUp);
					Boosts boostStruct;
					m_boost.printBoost(m_window, boostStruct, m_Board.getMoneyStatus());
					m_Board.useBoost(boostStruct);

					if (i == m_levels.size() - 2) // last level
						stopAndDisplay("lastLevel.jpg");
				}
			}
			else
			{
				stopAndDisplay("fail.png"); // player failed
				return true;
			}

		}
		stopAndDisplay("success.jpg"); // player success

		return true;
	}
	return false;
}

bool Controller::run(const short i)
{	
	if (!m_Board.readBoardFromFile(m_levels[i])) // read from file
		throw std::exception("Cant read File\n");

	m_bgPic.setScale(m_Board.getWidth() / m_bgPic.getLocalBounds().width, // backGround pic
		m_Board.getHeight() / m_bgPic.getLocalBounds().height);
		
	while (m_window.isOpen())
	{
		sf::Event event;
		
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();  
				break;
			}

			if (event.type == sf::Event::MouseButtonPressed) // Shoot Bullets
				m_Board.dealWithBullet(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::E) // Bomb
					m_Board.dealWithBomb();

				else if (event.key.code == sf::Keyboard::Z) // Teleport
					m_Board.dealWithTrans();

				chooseGun(event); // change the Bullets texture
			}
		}

		game();
		
		auto situation = m_Board.checkTerms();
		if (situation == Options::OutOfLife)
			return false;
		else if (situation == Options::MarcoSuccsess)
			return true;
	}
	return false;
}

void Controller::chooseGun(const sf::Event event)
{
	if (event.key.code == sf::Keyboard::Num1) // First Gun
		m_Board.changeBulletPic(Guns::Fire);

	else if (event.key.code == sf::Keyboard::Num2) // Second Gun
		m_Board.changeBulletPic(Guns::Blue);

	else if (event.key.code == sf::Keyboard::Num3) // Second Gun
		m_Board.changeBulletPic(Guns::Yellow);
}

void Controller::game()
{
	static sf::Clock clock;
	static float deltaTime;
	
	deltaTime = clock.restart().asSeconds();

	m_Board.ownerTurn();
	m_Board.eraseObject();
	m_Board.moveObject(deltaTime);
	m_Board.checkCollision();
	m_Board.getDetails(m_details);

	setCenter();
	m_window.clear();
	m_window.setView(m_view); //player
	m_window.draw(m_bgPic);
	m_Board.drawObject(m_window);
	Stats::instance().setViewAndPrint(m_window, m_details); //set view for stats
	m_window.display();
	m_window.setView(m_view);
	
}

void Controller::setCenter()
{
	auto curr = m_Board.getMarcoPos();
	auto boardLength = m_Board.getHeight();
	auto boardWidth = m_Board.getWidth();

	if (boardLength - curr.y > boardLength - Utilities::WINDOW_SIZE_HEIGHT / 2)
		curr.y = Utilities::WINDOW_SIZE_HEIGHT / 2;
	
	else if(boardLength - curr.y < Utilities::WINDOW_SIZE_HEIGHT / 2)
		curr.y = boardLength - Utilities::WINDOW_SIZE_HEIGHT / 2;

	if (boardWidth - curr.x > boardWidth - Utilities::WINDOW_SIZE_WITDH / 2)
		curr.x = Utilities::WINDOW_SIZE_WITDH / 2;

	else if (boardWidth - curr.x < Utilities::WINDOW_SIZE_WITDH / 2)
		curr.x = boardWidth - Utilities::WINDOW_SIZE_WITDH / 2;

	m_view.setCenter(curr);
}

void Controller::startAni() // the first Animation ("Video")
{
	sf::Sprite spr(ToolBar::instance().getPicture(UtilitiesChar::C_STARTANI));
	spr.setPosition(Utilities::WINDOW_SIZE_WITDH / 2 -300,
					Utilities::WINDOW_SIZE_HEIGHT / 2 -250);
	spr.setTextureRect(sf::IntRect(0, 0, 618, 400));

	m_window.clear();

	while (m_window.isOpen())
	{
		if (m_clockForstartAni.getElapsedTime().asSeconds() > 1.f)
		{
			sf::IntRect ir = spr.getTextureRect();
			if (spr.getTextureRect().left >= 3700)
			{
				break;
			}

			else
			{
				ir.left += 618;
				spr.setTextureRect(ir);
			}

			spr.setTextureRect(spr.getTextureRect());
			m_clockForstartAni.restart();
		}
		m_window.clear();
		m_window.draw(spr);
		m_window.display();

	}
}

void Controller::stopAndDisplay(const std::string s)
{
	m_view.reset({ 0.f, 0.f, Utilities::WINDOW_SIZE_WITDH,  Utilities::WINDOW_SIZE_HEIGHT });
	m_view.setViewport({ 0.f, 0.f, 1.f, 1.f });
	m_window.setView(m_view);
	

	sf::RectangleShape bgPic;
	sf::Texture bgTex;
	bgTex.loadFromFile(s);
	bgPic.setTexture(&bgTex);
	bgPic.setSize(sf::Vector2f(Utilities::WINDOW_SIZE_WITDH, Utilities::WINDOW_SIZE_HEIGHT));

	m_window.clear();
	m_window.draw(bgPic);
	m_window.display();
	Sleep(1500);
	m_window.clear();
	m_view.setViewport({ 0.f, 0.f, 1.f, 0.682f });
}