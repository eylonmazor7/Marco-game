 #include "Collision.h"

Collision& Collision::instance()
{
	static auto instance = Collision();
	return instance;
}

Collision::Collision()
{
	m_FuncMap[Key(typeid(Wall), typeid(Marco))] = &WallMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Wall))] = &MarcoWall;
	m_FuncMap[Key(typeid(Marco), typeid(Food))] = &MarcoFood;
	m_FuncMap[Key(typeid(Food), typeid(Marco))] = &FoodMarco;
	m_FuncMap[Key(typeid(Boss), typeid(Food))] = &BossFood;
	m_FuncMap[Key(typeid(Food), typeid(Boss))] = &FoodBoss;
	m_FuncMap[Key(typeid(Marco), typeid(Weapon))] = &MarcoWeapon;
	m_FuncMap[Key(typeid(Weapon), typeid(Marco))] = &WeaponMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Money))] = &MarcoMoney;
	m_FuncMap[Key(typeid(Money), typeid(Marco))] = &MoneyMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Treasure))] = &MarcoTreasure;
	m_FuncMap[Key(typeid(Treasure), typeid(Marco))] = &TreasureMarco;
	m_FuncMap[Key(typeid(Marco), typeid(LifeGift))] = &MarcoLGift;
	m_FuncMap[Key(typeid(LifeGift), typeid(Marco))] = &LGiftMarco;
	m_FuncMap[Key(typeid(Marco), typeid(WeaponGift))] = &MarcoWGift;
	m_FuncMap[Key(typeid(WeaponGift), typeid(Marco))] = &WGiftMarco;
	m_FuncMap[Key(typeid(Marco), typeid(MoneyGift))] = &MarcoMGift;
	m_FuncMap[Key(typeid(MoneyGift), typeid(Marco))] = &MGiftMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Door))] = &MarcoDoor;
	m_FuncMap[Key(typeid(Door), typeid(Marco))] = &DoorMarco;
	m_FuncMap[Key(typeid(Door), typeid(Owner))] = &DoorOwner;
	m_FuncMap[Key(typeid(Owner), typeid(Door))] = &OwnerDoor;
	m_FuncMap[Key(typeid(Owner), typeid(Wall))] = &OwnerWall;
	m_FuncMap[Key(typeid(Wall), typeid(Owner))] = &WallOwner;
	m_FuncMap[Key(typeid(Boss), typeid(MarcoBullet))] = &BossMbullet;
	m_FuncMap[Key(typeid(MarcoBullet), typeid(Boss))] = &MbulletBoss;
	m_FuncMap[Key(typeid(Owner), typeid(MarcoBullet))] = &OwnerMBullet;
	m_FuncMap[Key(typeid(MarcoBullet), typeid(Owner))] = &MBulletOwner;
	m_FuncMap[Key(typeid(Wall), typeid(Kofifo))] = &WallKofifo;
	m_FuncMap[Key(typeid(Kofifo), typeid(Wall))] = &KofifoWall;
	m_FuncMap[Key(typeid(Door), typeid(Kofifo))] = &DoorKofifo;
	m_FuncMap[Key(typeid(Kofifo), typeid(Door))] = &KofifoDoor;
	m_FuncMap[Key(typeid(MarcoBullet), typeid(Kofifo))] = &MBulletKofifo;
	m_FuncMap[Key(typeid(Kofifo), typeid(MarcoBullet))] = &KofifoMBullet;
	m_FuncMap[Key(typeid(Food), typeid(Kofifo))] = &FoodKofifo;
	m_FuncMap[Key(typeid(Kofifo), typeid(Food))] = &KofifoFood;
	m_FuncMap[Key(typeid(Owner), typeid(Marco))] = &OwnerMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Owner))] = &MarcoOwner;
	m_FuncMap[Key(typeid(Kofifo), typeid(Marco))] = &KofifoMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Kofifo))] = &MarcoKofifo;
	m_FuncMap[Key(typeid(Kofifo), typeid(Owner))] = &KofifoOwner;
	m_FuncMap[Key(typeid(Owner), typeid(Kofifo))] = &OwnerKofifo;
	m_FuncMap[Key(typeid(Wall), typeid(MarcoBullet))] = &WallMBullet;
	m_FuncMap[Key(typeid(MarcoBullet), typeid(Wall))] = &MBulletWall;
	m_FuncMap[Key(typeid(Door), typeid(MarcoBullet))] = &DoorMBullet;
	m_FuncMap[Key(typeid(MarcoBullet), typeid(Door))] = &MBulletDoor;
	m_FuncMap[Key(typeid(OwnerBullet), typeid(Kofifo))] = &OBulletKofifo;
	m_FuncMap[Key(typeid(Kofifo), typeid(OwnerBullet))] = &KofifoOBullet;
	m_FuncMap[Key(typeid(Marco), typeid(OwnerBullet))] = &MarcoOBullet;
	m_FuncMap[Key(typeid(OwnerBullet), typeid(Marco))] = &OBulletMarco;
	m_FuncMap[Key(typeid(Wall), typeid(OwnerBullet))] = &WallOBullet;
	m_FuncMap[Key(typeid(OwnerBullet), typeid(Wall))] = &OBulletWall;
	m_FuncMap[Key(typeid(Door), typeid(OwnerBullet))] = &DoorOBullet;
	m_FuncMap[Key(typeid(OwnerBullet), typeid(Door))] = &OBulletDoor;
	m_FuncMap[Key(typeid(Boss), typeid(Marco))] = &BossMarco;
	m_FuncMap[Key(typeid(Marco), typeid(Boss))] = &MarcoBoss;
	m_FuncMap[Key(typeid(BossBullet), typeid(Marco))] = &BBulletMarco;
	m_FuncMap[Key(typeid(Marco), typeid(BossBullet))] = &MarcoBBullet;
}

void Collision::CollisionFunc(Object& a, Object& b)
{
	auto funcPtrCollision = getFuncPtr(typeid(a), typeid(b));

	if (!funcPtrCollision)
		return;

	funcPtrCollision(a, b);
}

funcPtr Collision::getFuncPtr(const std::type_index& class1, const std::type_index& class2)
{
	auto collisionFunc = m_FuncMap.find(std::make_pair(class1, class2));

	if (collisionFunc == m_FuncMap.end())
		return nullptr;

	return collisionFunc->second;
}

//////////////////////////// ---------------  Collision function  ------------ /////////////////////////////////////////

void MarcoWall(Object& marco1, Object& wall)
{
	Marco& marco = static_cast<Marco&>(marco1);
	marco.moveBack();
}

void BossFood(Object& boss1, Object& food1)
{
	Boss& marco = static_cast<Boss&>(boss1);
	Food& food = static_cast<Food&>(food1);

	food.setExist(false);
}

void MarcoFood(Object& marco1, Object& food1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Food& food = static_cast<Food&>(food1);

	marco.setFood(1);
	food.setExist(false);
}

void MarcoWeapon(Object& marco1, Object& weapon1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Weapon& weapon = static_cast<Weapon&>(weapon1);

	marco.setBulletsCapacity(rand() % 50);
	weapon.setExist(false);
}

void MarcoMoney(Object& marco1, Object& money1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Money& money = static_cast<Money&>(money1);

	marco.setMoney(10);
	money.setExist(false);
}

void MarcoTreasure(Object& marco1, Object& treasure1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Treasure& treasure = static_cast<Treasure&>(treasure1);
	
	marco.setTreasureKey(-1);
	treasure.setExist(false);
}

void MarcoLGift(Object& marco1, Object& gift1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	LifeGift& gift = static_cast<LifeGift&>(gift1);

	marco.setHP(Utilities::GIFT_PRIZE);
	gift.setExist(false);
}

void MarcoWGift(Object& marco1, Object& gift1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	WeaponGift& gift = static_cast<WeaponGift&>(gift1);

	marco.setBulletsCapacity(Utilities::GIFT_PRIZE);
	gift.setExist(false);
}

void MarcoMGift(Object& marco1, Object& gift1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	MoneyGift& gift = static_cast<MoneyGift&>(gift1);

	marco.setMoney(Utilities::GIFT_PRIZE);
	gift.setExist(false);
}

void MarcoDoor(Object& marco1, Object& door1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	marco.checkDoorKeyTerms();
}

void MBulletWall(Object& bullet1, Object& wall)
{
	MarcoBullet& bullet = static_cast<MarcoBullet&>(bullet1);
	bullet.setExist(false);
}

void MBulletDoor(Object& bullet1, Object&)
{
	MarcoBullet& bullet = static_cast<MarcoBullet&>(bullet1);
	bullet.setExist(false);
}

void MarcoBBullet(Object& marco1, Object& bullet1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	BossBullet& bullet = static_cast<BossBullet&>(bullet1);
	bullet.setExist(false);
	marco.setHP(Weapons::BOSS_BULLET_EFFECT);
}

void BBulletMarco(Object& bullet, Object& marco)
{
	MarcoBBullet(marco, bullet);
}

void WallMBullet(Object& wall, Object& bullet)
{
	MBulletWall(bullet, wall);
}

void DoorMBullet(Object& door, Object& bullet)
{
	MBulletDoor(bullet, door);
}

void OwnerDoor(Object& owner1, Object&)
{
	Owner& owner = static_cast<Owner&>(owner1);
	owner.moveBack();
}

void OwnerWall(Object& owner1, Object&)
{
	Owner& owner = static_cast<Owner&>(owner1);
	owner.moveBack();
}

void OwnerMBullet(Object& owner1, Object& bullet1)
{
	Owner& owner = static_cast<Owner&>(owner1);
	MarcoBullet& bullet = static_cast<MarcoBullet&>(bullet1);
	owner.setHP(Weapons::MARCO_BULLET_EFFECT);
	bullet.setExist(false);
}

void KofifoWall(Object& kofifo1, Object&)
{
	Kofifo& kofifo = static_cast<Kofifo&>(kofifo1);
	//kofifo.moveBack();
}

void KofifoDoor(Object& kofifo1, Object&)
{
	Kofifo& kofifo = static_cast<Kofifo&>(kofifo1);
	kofifo.moveBack();
}

void KofifoMBullet(Object& kofifo1, Object& bullet1)
{
}

void KofifoFood(Object& kofifo1, Object& food1)
{
	Food& food = static_cast<Food&>(food1);
	food.setExist(false);
}

void MarcoOwner(Object& marco1, Object& owner1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Owner& owner = static_cast<Owner&>(owner1);
	marco.setHP(-5);
	owner.setHP(20);
	marco.moveBack();
	owner.moveBack();
}

void MarcoKofifo(Object& marco1, Object& kofifo1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Kofifo& kofifo = static_cast<Kofifo&>(kofifo1);
	kofifo.changePos(true);
	marco.marcoKofifoCol();
}

void KofifoOwner(Object& kofifo1, Object& owner1)
{
	Kofifo& kofifo = static_cast<Kofifo&>(kofifo1);
	Owner& owner = static_cast<Owner&>(owner1);
	kofifo.moveBack();
	owner.moveBack();
	owner.setHP(-5);
}

void MarcoBoss(Object& marco1, Object& boss1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	Boss& boss = static_cast<Boss&>(boss1);
	marco.setHP(-20);
}

void BossMbullet(Object& boss1, Object& bullet1)
{
	Boss& boss = static_cast<Boss&>(boss1);
	MarcoBullet& bullet = static_cast<MarcoBullet&>(bullet1);
	
	boss.setHP(Weapons::MARCO_BULLET_EFFECT);
	bullet.setExist(false);
}

void MbulletBoss(Object& bullet, Object& boss)
{
	BossMbullet(boss, bullet);
}

void BossMarco(Object& boss, Object& marco)
{
	MarcoBoss(marco, boss);
}

void OwnerMarco(Object& owner, Object& marco)
{
	MarcoOwner(marco, owner);
}

void OwnerKofifo(Object& owner, Object& kofifo)
{
	KofifoOwner(kofifo, owner);
}

void KofifoMarco(Object& kofifo, Object& marco)
{
	MarcoKofifo(marco, kofifo);
}

void FoodKofifo(Object& food, Object& kofifo)
{
	KofifoFood(kofifo, food);
}

void MBulletKofifo(Object& bullet, Object& kofifo)
{
	KofifoMBullet(kofifo, bullet);
}

void DoorKofifo(Object& door, Object& kofifo)
{
	KofifoDoor(kofifo, door);
}

void WallKofifo(Object& wall, Object& kofifo)
{
	KofifoWall(kofifo, wall);
}

void DoorOwner(Object& door, Object& owner)
{
	OwnerDoor(owner, door);
}

void FoodBoss(Object& food, Object& boss)
{
	BossFood(boss, food);
}

void WallOwner(Object& wall, Object& owner)
{
	OwnerWall(owner, wall);
}

void MBulletOwner(Object& bullet, Object& owner)
{
	OwnerMBullet(owner, bullet);
}

void DoorMarco(Object& door, Object& marco)
{
	MarcoDoor(marco, door);
}

void LGiftMarco(Object& gift, Object& marco)
{
	MarcoLGift(marco, gift);
}

void MGiftMarco(Object& gift, Object& marco)
{
	MarcoMGift(marco, gift);
}

void WGiftMarco(Object& gift, Object& marco)
{
	MarcoWGift(marco, gift);
}

void TreasureMarco(Object& treasure, Object& marco)
{
	MarcoTreasure(marco, treasure);
}

void MoneyMarco(Object& money, Object& marco)
{
	MarcoMoney(marco, money);
}

void WeaponMarco(Object& weapon, Object& marco)
{
	MarcoWeapon(marco, weapon);
}

void WallMarco(Object& wall, Object& marco)
{
	MarcoWall(marco, wall);
}

void FoodMarco(Object& food, Object& marco)
{
	MarcoFood(marco, food);
}

void OBulletKofifo(Object& bullet, Object& kofifo)
{
	KofifoOBullet(kofifo, bullet);
}

void KofifoOBullet(Object&, Object&)
{
	//code
}

void MarcoOBullet(Object& marco1, Object& bullet1)
{
	Marco& marco = static_cast<Marco&>(marco1);
	OwnerBullet& bullet = static_cast<OwnerBullet&>(bullet1);
	marco.setHP(Weapons::OWNER_BULLET_EFFECT);
	bullet.setExist(false);
}

void OBulletMarco(Object& bullet, Object& marco)
{
	MarcoOBullet(marco, bullet);
}

void WallOBullet(Object& wall, Object& bullet)
{
	OBulletWall(bullet, wall);
}

void OBulletWall(Object& bullet1, Object&)
{
	OwnerBullet& bullet = static_cast<OwnerBullet&>(bullet1);
	bullet.setExist(false);
}

void DoorOBullet(Object& door, Object& bullet)
{
	OBulletDoor(bullet, door);
}

void OBulletDoor(Object& bullet1, Object&)
{
	OwnerBullet& bullet = static_cast<OwnerBullet&>(bullet1);
	bullet.setExist(false);
}
