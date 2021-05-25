#pragma once
#include "Gift.h"

class LifeGift : public Gift
{
public:
	using Gift::Gift;
	virtual ~LifeGift() = default;
};