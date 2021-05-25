#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <Utilities.h>
#include <unordered_map>

class ToolBar
{
public:
	static ToolBar& instance();
	~ToolBar() = default;

	sf::Sprite& getPicture(char c);

private:
	ToolBar();
	ToolBar(const ToolBar&) = delete;
	ToolBar& operator= (const ToolBar&) = delete;

	sf::Texture m_Textures[UtilitiesChar::SIZE_OF_TOOLBAR];
	std::unordered_map <char, sf::Sprite> m_map;
};