#pragma once
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(sf::Vector2f, sf::Sprite);
	Object() = default;
	virtual ~Object() = default;

	void setStart(sf::Vector2f& pos, sf::Sprite);
	
	bool getExist() const;
	void setExist(bool);

	sf::Sprite& getSprite();
	sf::Vector2f getStartPos() const;
	sf::IntRect getTextureRect();
	
	void draw(sf::RenderWindow&) const;
	
private:
	bool m_exist = true;
	sf::Vector2f m_StartPos = sf::Vector2f(0.0f, 0.0f);
	sf::Sprite m_Sprite;
};