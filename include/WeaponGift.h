#pragma once
#include "Gift.h"

class WeaponGift : public Gift
{
public:
	using Gift::Gift;
	virtual ~WeaponGift() = default;
};