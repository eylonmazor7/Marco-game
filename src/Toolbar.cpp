#pragma once

#include <Toolbar.h>

ToolBar& ToolBar::instance()
{
	static auto instance = ToolBar();
	return instance;
}

ToolBar::ToolBar()
{
	std::string iconsNames[UtilitiesChar::SIZE_OF_TOOLBAR] =
	{ "111.png" , "monkey.png", "owner.png", "wall.png", "weapon.png",
		"food.png", "money.png", "treasure.png", "gift.png", "door.png",
		"BulletBlue.png", "bomb.png", "Teleport.png","fireBullet.png" ,
		"dragon2.png", "fireBall.png", "BulletYellow.png", "startAni.png" };

	for (int i = 'A', k = 0; k < UtilitiesChar::SIZE_OF_TOOLBAR; k++, i++)
	{
		if (!m_Textures[k].loadFromFile(iconsNames[k]))
			throw std::exception("Cannot open picture \n");

		m_map[char(i)].setTexture(m_Textures[k]);

		if (k == 0) // marco
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 50, 31));
		else if (k == 1) // kofifo
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 47, 48));
		else if (k == 2) // owner
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 37, 50));
		else if (k == 12) // bomb
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 41, 50));
		else if (k == 13) // Teleport
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 27, 50));
		else if (k == 15) // dragon
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 50, 50));
		else if (k == 15) // startAni for controller
			continue;
		else
			m_map[char(i)].setTextureRect(sf::IntRect(0, 0, 50, 50));
	}
}

sf::Sprite& ToolBar::getPicture(char c)
{
	return m_map[c];
}
