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
		std::cout << "  ------------\n ERROR: soundBuffer already exists. \n  -------------";
	}	
	

}

// Musiken streamas in automatiskt så den behöver ej finnas i manager
/*
void SoundManager::addMusic(const std::string&_filename) 
{
	std::string path = m_dir + _filename;
	sf::Music music;
	music.openFromFile(path);

	std::map<std::string, sf::Music>::iterator it = m_music.find(_filename);
	if (it == m_music.end())
	{
		m_music.insert( std::pair<std::string, sf::Music>(_filename, music));
	}
	else
	{
		std::cout << "  ------------\n ERROR: Music already exists. \n  -------------";
}*/

/*
sf::SoundBuffer* SoundManager::getSound(const std::string& _name)
	}

}
*/
sf::Sound* SoundManager::GetSound(const std::string& _filename)
{
	sf::Sound* sound = new sf::Sound();
	
	std::map<std::string, sf::SoundBuffer>::iterator it = m_soundBuffer.find(_filename);
	if ( it == m_soundBuffer.end())
	{
		std::cout << "  ------------\n ERROR: SoundBuffer does not exist. \n  -------------";
		return nullptr;
	}

	sound->setBuffer(it->second);
	
	return sound;

}
/*
sf::Music* SoundManager::GetMusic(const std::string& _filename)
{


}
*/
