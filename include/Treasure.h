#pragma once
#include "StaticObject.h"

class Treasure : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual ~Treasure() = default;
};