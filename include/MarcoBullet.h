#pragma once
#include "Bullet.h"

class MarcoBullet : public Bullet
{
public:
	using Bullet::Bullet;
	virtual ~MarcoBullet() = default;
};