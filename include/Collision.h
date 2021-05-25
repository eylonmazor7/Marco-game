#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <typeinfo>
#include "BossBullet.h"
#include "OwnerBullet.h"
#include "MarcoBullet.h"
#include "Object.h"
#include "Marco.h"
#include "Owner.h"
#include "Kofifo.h"
#include "Wall.h"
#include "Treasure.h"
#include "Weapon.h"
#include "Food.h"
#include "Money.h"
#include "Bullet.h"
#include "Door.h"
#include "LifeGift.h"
#include "MoneyGift.h"
#include "WeaponGift.h"
#include "Utilities.h"
#include "Boss.h"

//type def
using funcPtr = void (*)(Object&, Object&);
using Key = std::pair<std::type_index, std::type_index>;

class Collision
{
public:
	static Collision& instance();
	void CollisionFunc(Object&, Object&);

private:
	Collision();
	Collision(const Collision&) = delete;
	Collision& operator= (const Collision&) = delete;

	funcPtr getFuncPtr(const std::type_index&, const std::type_index&);
	std::map <Key, funcPtr> m_FuncMap;
};

//collision func
//marco <-> static

void WallMarco(Object&, Object&);
void MarcoWall(Object&, Object&);

void FoodMarco(Object&, Object&);
void MarcoFood(Object&, Object&);

void WeaponMarco(Object&, Object&);
void MarcoWeapon(Object&, Object&);

void MoneyMarco(Object&, Object&);
void MarcoMoney(Object&, Object&);

void TreasureMarco(Object&, Object&);
void MarcoTreasure(Object&, Object&);

void LGiftMarco(Object&, Object&);
void MarcoLGift(Object&, Object&);

void MGiftMarco(Object&, Object&);
void MarcoMGift(Object&, Object&);

void WGiftMarco(Object&, Object&);
void MarcoWGift(Object&, Object&);

void DoorMarco(Object&, Object&);
void MarcoDoor(Object&, Object&);

//
//Owner <-> static
void WallOwner(Object&, Object&);
void OwnerWall(Object&, Object&);

void DoorOwner(Object&, Object&);
void OwnerDoor(Object&, Object&);

void MBulletOwner(Object&, Object&);
void OwnerMBullet(Object&, Object&);

void FoodBoss(Object&, Object&);
void BossFood(Object&, Object&);

//
//kofifo <-> static
void WallKofifo(Object&, Object&);
void KofifoWall(Object&, Object&);

void DoorKofifo(Object&, Object&);
void KofifoDoor(Object&, Object&);

void MBulletKofifo(Object&, Object&);
void KofifoMBullet(Object&, Object&);

void FoodKofifo(Object&, Object&);
void KofifoFood(Object&, Object&);
//
//bullets
void WallMBullet(Object&, Object&);
void MBulletWall(Object&, Object&);

void DoorMBullet(Object&, Object&);
void MBulletDoor(Object&, Object&);

void OBulletKofifo(Object&, Object&);
void KofifoOBullet(Object&, Object&);

void MarcoOBullet(Object&, Object&);
void OBulletMarco(Object&, Object&);

void WallOBullet(Object&, Object&);
void OBulletWall(Object&, Object&);

void DoorOBullet(Object&, Object&);
void OBulletDoor(Object&, Object&);

void BossMbullet(Object&, Object&);
void MbulletBoss(Object&, Object&);

void BBulletMarco(Object&, Object&);
void MarcoBBullet(Object&, Object&);

// mobile Object Collision
void OwnerMarco(Object&, Object&);
void MarcoOwner(Object&, Object&);

void KofifoMarco(Object&, Object&);
void MarcoKofifo(Object&, Object&);

void KofifoOwner(Object&, Object&);
void OwnerKofifo(Object&, Object&);

void BossMarco(Object&, Object&);
void MarcoBoss(Object&, Object&);
