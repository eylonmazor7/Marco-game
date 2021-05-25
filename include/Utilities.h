#pragma once

enum class Sounds
{
	gunFire,
	bombSound,
	flash,
	points,
	levelUp
};

enum class Guns
{
	Fire,
	Blue,
	Yellow
};

enum class Options
{
	OutOfLife,
	MarcoSuccsess,
	Nothing
};

enum class textEnum
{
	treasure,
	HP,
	Bombs,
	Money,
	Level,
	Food,
	Ammo,
	Tele
};

enum class Choice
{
	E_instructions,
	E_startGame,
	E_exitGame
};

struct Boosts
{
	bool HP = false;
	bool marcoSpeed = false;
	bool kofifoSpeed = false;
	bool bombs = false;
	bool teleports = false;
};

struct Details
{
	int level;
	int money;
	int HP;
	int food;
	int ammo;
	int bomb;
	int tele;
	int keys;
};

namespace Utilities
{
	const unsigned WINDOW_SIZE_HEIGHT = 850;
	const unsigned WINDOW_SIZE_WITDH = 1100;
	const unsigned CHAR_SIZE = 22;
	const int BOOST_COST = 50;
	const int MENU_SIZE = 3;
	const int MARCO_TRANS_TIMES = 5;
	const int TOOLBAR_DATA = 8;
	const int MARCO_FOOD = 5;
	const int BOOST_NUM = 5;
	const int KOFIFO_PRIZE = 10;
	const float KOFIFO_DISTANCE = 500;
	const float SIZE_OF_PIC = 50;
	const int GIFT_PRIZE = 20;
}

namespace Weapons
{
	const int BOSS_BULLET_EFFECT = 15;
	const int MARCO_BULLET_EFFECT = 20;
	const int OWNER_BULLET_EFFECT = 15;
	const double SHOOTING_RANGE = 256;
	const double BOMB_RADIUS = 150;
	const float BOSS_BULLET_RANGE = 500;
	const int BOSS_RATE_OF_FIRE = 75;
	const int OWNER_RATE_OF_FIRE = 85;
	const int BOMB_CAPA = 5;
	const int BULLETS_CAPA = 30;
	const int BOMB_EFFECTS = -100;
}

namespace Life
{
	const int LIFE_OF_OWNER = 100;
	const int LIFE_OF_BOSS = 500;
	const int LIFE_OF_MARCO = 150;
}

namespace Speed
{
	const float BOSS_BULLET_SPEED = 3.5;
	const float OWNER_BULLET_SPEED = 3;
	const float MARCO_BULLET_SPEED = 5;
	const float MARCO_SPEED = 300;
	const float OWNER_SPEED = 45;
	const float BOSS_SPEED = 50;
	const float KOFIFO_SPEED = 50;
}

namespace UtilitiesChar
{
	const int SIZE_OF_TOOLBAR = 18;

	const char C_MARCO          = 'A';
	const char C_KOFIFO         = 'B';
	const char C_OWNER          = 'C';
	const char C_WALL           = 'D';
	const char C_WEAPON         = 'E';
	const char C_FOOD           = 'F';
	const char C_MONEY          = 'G';
	const char C_TREASURE       = 'H';
	const char C_GIFT           = 'I';
	const char C_DOOR           = 'J';
	const char C_BULLET         = 'K';
	const char C_BOMB           = 'L';
	const char C_Teleport = 'M';
	const char C_ANOTHERBULLET  = 'N';
	const char C_BOSS           = 'O';
	const char C_BOSSBULLET     = 'P';
	const char C_ANOTHERBULLET2 = 'Q';
	const char C_STARTANI       = 'R';
}