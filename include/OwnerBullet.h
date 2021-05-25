#pragma once
#include "Bullet.h"

class OwnerBullet : public Bullet
{
public:
	using Bullet::Bullet;
	virtual ~OwnerBullet() = default;
};