#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <Utilities.h>
#include <unordered_map>
#include <SFML/Audio.hpp>

class SoundEffects
{
public:
	static SoundEffects& instance();
	~SoundEffects() = default;
	
	sf::SoundBuffer& getSound(int);
	
private:
	static const int SOUNDSSIZE = 5;

	SoundEffects();
	SoundEffects(const SoundEffects&) = delete;
	SoundEffects& operator= (const SoundEffects&) = delete;

	sf::SoundBuffer m_SoundArr[SOUNDSSIZE];
};