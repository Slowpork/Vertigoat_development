// SoundManager.cpp

#include "SoundManager.h"
#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "SFML\Audio\Music.hpp"


#include <iostream>

SoundManager::SoundManager(std::string _dir)
{
	m_dir = _dir;
}

void SoundManager::addSound(const std::string& _filename)
{
	std::string path = m_dir + _filename;
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile(path);

	std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffer.find(_filename);
	if (it == m_soundBuffer.end())
		m_soundBuffer.insert( std::pair<std::string, sf::SoundBuffer>(_filename, soundBuffer));
	else
		std::cout << "  ------------\n ERROR: soundBuffer already exists. \n  -------------";
}

sf::SoundBuffer* SoundManager::getSound(const std::string& _name)
{
	std::map<std::string,sf::SoundBuffer>::iterator it = m_soundBuffer.find(_name);
	if (it == m_soundBuffer.end())
		return nullptr;
	else
	return &it->second;
}


