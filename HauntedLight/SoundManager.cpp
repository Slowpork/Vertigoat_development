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

SoundManager::~SoundManager()
{

}

void SoundManager::addSoundBuffer(const std::string& _filename)
{
	std::string path = m_dir + _filename;
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile(path);


	std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffer.find(_filename);
	if (it == m_soundBuffer.end())
	{
		m_soundBuffer.insert( std::pair<std::string, sf::SoundBuffer>(_filename, soundBuffer));
	}
	else
	{
		std::cout << "  ------------\n ERROR: soundBuffer: " << _filename << " already exists. \n  -------------";
	}
}

sf::Sound* SoundManager::getSound(const std::string& _filename)
{
	sf::Sound* sound = new sf::Sound();
	
	std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffer.find(_filename);
	if ( it == m_soundBuffer.end())
	{
		std::cout << "  ------------\n ERROR: SoundBuffer: " << _filename << " does not exist. \n  -------------";
		return nullptr;
	}

	sound->setBuffer(it->second);
	
	return sound;
}

sf::Music* SoundManager::getMusic(const std::string& _filename)
{
	sf::Music* music = new sf::Music();
	
	if ( !music->openFromFile(m_dir + _filename))
	{
		std::cout << "  ------------\n ERROR: Music: " << _filename << " could not be opened. \n  -------------";
		return nullptr;
	}

	return music;
}
