#pragma once
#include "StaticObject.h"

class Food : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual ~Food () = default;
};