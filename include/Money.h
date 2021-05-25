 #pragma once
#include <SFML/Graphics.hpp>

class Money : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual ~Money() = default;
};