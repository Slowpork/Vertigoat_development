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

	void addSoundBuffer(const std::string& _filename);
	void addMusic(const std::string&_filename);
	sf::Sound* getSound(const std::string& _filename);
	sf::Music* getMusic(const std::string& _filename);
	
	void Cleanup();

private:

private:
	std::string m_dir;
	std::map<std::string,sf::SoundBuffer> m_soundBuffer;
	std::map<std::string,sf::Music> m_music;

};