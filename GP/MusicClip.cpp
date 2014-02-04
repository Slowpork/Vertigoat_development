// MusicClip.cpp

#include "stdafx.h"

#include "MusicClip.h"

/*

MusicClip::MusicClip()
{
	clip = nullptr;
	channel = -1;
}

MusicClip::~MusicClip()
{
	clip = nullptr;
	channel = -1;
}

MusicClip::MusicClip(Mix_Music *_clip)
{
	clip = _clip;
	channel = -1;
}

void MusicClip::Play()
{
	channel = Mix_PlayMusic(clip, -1);
}

void MusicClip::Pause()
{
	if ( channel == -1 )
		return;

	if ( Mix_PausedMusic() )
		Mix_ResumeMusic();
	else
		Mix_Pause(channel);
}

void MusicClip::Volume(int _volume)
{
	Mix_VolumeMusic(_volume);
}

void MusicClip::Stop()
{
	if ( channel == -1)
		return;

	Mix_HaltChannel(channel);
	channel = -1;
}

*/