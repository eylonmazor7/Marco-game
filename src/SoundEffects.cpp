#pragma once

#include "SoundEffects.h"

SoundEffects& SoundEffects::instance()
{
	static auto instance = SoundEffects();
	return instance;
}

SoundEffects::SoundEffects()
{
	std::string iconsNames[SOUNDSSIZE] = 
	{ "gunFire.ogg", "bombSound.ogg", "flash.ogg", "points.ogg", "levelUp.ogg"};

	for (int i = 0; i < SOUNDSSIZE; i++)
	{
		if (!m_SoundArr[i].loadFromFile(iconsNames[i]))
			throw std::exception("Cannot open Music \n");
	}
}

sf::SoundBuffer& SoundEffects::getSound(int i)
{
	return m_SoundArr[i];
}
