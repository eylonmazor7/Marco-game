#pragma once
#include "Gift.h"

class MoneyGift : public Gift
{
public:
	using Gift::Gift;
	virtual ~MoneyGift() = default;
};