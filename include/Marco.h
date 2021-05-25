#pragma once
#include"MobileObject.h"
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class Marco : public MobileObject
{
public:
	Marco();
	virtual ~Marco() = default;
	
	//set
	virtual sf::Vector2f setDirection(float, sf::Vector2f&) override;
	void setHP(int);
	void setFood(int);
	void setReady(bool);
	void setBulletsCapacity(int);
	void setBombsCapacity(int);
	void setTreasureKey(int);
	void setTrans(int);
	void setMoney(int);
	
	//get
	sf::Vector2f getLastDirection();
	int getMoney() const;
	int getHP() const;
	int getFood() const;
	int getReady() const;
	int getBulletsCapacity() const;
	int getBombsCapacity() const;
	int getTransTimes() const;
	int getTreasureKey() const;
	
	void marcoKofifoCol();
	void restartKeys();
	void checkDoorKeyTerms();
	void setDetails();

private:
	int m_booletCapacity = Weapons::BULLETS_CAPA;
	int m_BombCapacity = Weapons::BOMB_CAPA;
	int m_transTimes = Utilities::MARCO_TRANS_TIMES;
	int m_life = Life::LIFE_OF_MARCO;
	int m_food = Utilities::MARCO_FOOD;
	int m_TreasureKey = 0;
	int m_money = 0;
	bool m_readyToNext = false;
	sf::Vector2f LastDirection;
};