// SoundManager.h

#pragma once
#include <string>
#include <vector>
#include <map>
#include <SFML\Audio\Sound.hpp>

namespace sf
{
	class Sound;
	class Music;
}


class SoundManager
{
public:
	SoundManager(std::string _dir);
	~SoundManager();

	void addSound(const std::string& _filename);
	sf::SoundBuffer* getSound(const std::string& _name);
	
	void Cleanup();

private:

private:
	std::string m_dir;
	std::map<std::string,sf::SoundBuffer> m_soundBuffer;

};