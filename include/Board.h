#pragma once

#include <iostream>
#include <math.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Owner.h"
#include "Utilities.h"
#include "Marco.h"
#include "Object.h"
#include "Toolbar.h"
#include "Menu.h"
#include "MobileObject.h"
#include "Gift.h"
#include "Food.h"
#include "Wall.h"
#include "Door.h"
#include "Money.h"
#include "LifeGift.h"
#include "MoneyGift.h"
#include "WeaponGift.h"
#include "Board.h"
#include "Kofifo.h"
#include "Weapon.h"
#include "Treasure.h"
#include "Collision.h"
#include "SfmlCollision.h"
#include "Bomb.h"
#include "Teleport.h"
#include "Boss.h"
#include "Boost.h"
#include "BossBullet.h"
#include "SoundEffects.h"

class Board
{
public:
	Board() = default;
	~Board() = default; 
	
	void cleanDetails(bool);
	const sf::Vector2f getMarcoPos() const;
	const Options checkTerms();
	bool readBoardFromFile(const std::string);
	void checkCollision();
	void useBoost(const Boosts);
	void dealWithSound(Sounds i);
	void drawObject(sf::RenderWindow&) const;
	void getDetails(struct Details&) const;
	void moveObject(const float);
	void dealWithBullet(sf::Vector2f);
	void dealWithBomb();
	void dealWithTrans();
	void changeBulletPic(Guns);
	void ownerTurn();
	void eraseObject();
	int getMoneyStatus() const;
	float getHeight() const;
	float getWidth() const;

private:
	void checkBombEffect(int);
	double calcDistance(const sf::Vector2f& v1, const sf::Vector2f& v2) const;
	sf::Vector2f checkDirectionToMarco(const sf::Vector2f&) const;

	std::vector <std::unique_ptr<StaticObject>> m_staticObject; 
	std::vector<std::unique_ptr<MarcoBullet>> m_marcoBullets;
	std::vector<std::unique_ptr<BossBullet>> m_bossBullets;
	std::vector<std::unique_ptr<OwnerBullet>> m_ownerBullets;
	std::vector<std::unique_ptr<Owner>> m_Owners;
	std::vector<std::unique_ptr<Bomb>> m_Bombs;
	std::vector<std::unique_ptr<Teleport>> m_Trans;
	std::vector<sf::Vector2f> m_FreePlaces;
	
	Marco m_Marco;
	Kofifo m_Kofifo;
	Boss m_Boss;

	sf::Sprite m_BulletSprite = ToolBar::instance().getPicture(UtilitiesChar::C_BULLET);
	sf::Sound m_Sound;

	int m_rowSize = 0;
	int m_colSize = 0;
};
