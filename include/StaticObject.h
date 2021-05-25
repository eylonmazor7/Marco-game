#pragma once
#include "Object.h"

class StaticObject : public Object
{
public:
	using Object::Object;
	virtual ~StaticObject() = default;
};