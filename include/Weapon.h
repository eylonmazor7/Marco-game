#pragma once
#include "StaticObject.h"

class Weapon : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual ~Weapon() = default;
};