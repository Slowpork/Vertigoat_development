// SoundManager


#include "stdafx.h"

/*
#include "SoundManager.h"
#include "MusicClip.h"
#include "SoundClip.h"

#pragma comment(lib,"sdl2_mixer.lib")



SoundManager::SoundManager()
{
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0)
	{
		printf(" SDL_mixer :: Msx_OpenAudio %s\n", Mix_GetError());
	}
}

SoundManager::~SoundManager()
{
	for(int i = 0; i < SoundClips.size(); i++)
	{
		delete SoundClips[i];
		SoundClips[i] = nullptr;
	}
	SoundClips.clear();

	for(int i = 0; i < MusicClips.size(); i++)
	{
		delete MusicClips[i];
		MusicClips[i] = nullptr;
	}
	MusicClips.clear();

	{
		std::map<std::string, Mix_Chunk*>::iterator it = Sounds.begin();
		while( it != Sounds.end())
		{
			Mix_FreeChunk(it->second);
			it->second = nullptr;
			it++;
		}
		Sounds.clear();
	}

	{
		std::map<std::string, Mix_Music*>::iterator it = Music.begin();
		while( it != Music.end())
		{
			Mix_FreeMusic(it->second);
			it->second = nullptr;
			it++;
		}
		Music.clear();
	}
}

MusicClip *SoundManager::CreateMusic(std::string _path)
{
	MusicClip *Ret = nullptr;

	std::map<std::string, Mix_Music*>::iterator it = Music.find(_path);

	if ( it == Music.end())
	{
		Mix_Music *Music = Mix_LoadMUS(_path.c_str());
		std::pair<std::string, Mix_Music*> Pair;
		Pair = std::make_pair(_path, Music);
		Ret = new MusicClip(Music);
	}
	else
		Ret = new MusicClip(it->second);

	MusicClips.push_back(Ret);

	return Ret;
}

SoundClip *SoundManager::CreateSound(std::string _path)
{
	SoundClip *Ret = nullptr;

	std::map<std::string, Mix_Chunk*>::iterator it = Sounds.find(_path);

	if ( it == Sounds.end())
	{
		Mix_Chunk *Sound = Mix_LoadWAV(_path.c_str());
		std::pair<std::string, Mix_Chunk*> Pair;
		Pair = std::make_pair(_path, Sound);
		Ret = new SoundClip(Sound);
	}
	else
		Ret = new SoundClip(it->second);

	SoundClips.push_back(Ret);

	return Ret;
}

*/