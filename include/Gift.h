#pragma once
#include "StaticObject.h"

class Gift : public StaticObject
{
public:
	using StaticObject::StaticObject;
	virtual ~Gift() = default;
};