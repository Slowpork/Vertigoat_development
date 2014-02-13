// SoundClip.cpp



#include "SoundClip.h"

/*

SoundClip::SoundClip()
{
	clip = nullptr;
	channel = -1;
}

SoundClip::~SoundClip()
{
	clip = nullptr;
	channel = -1;
}

SoundClip::SoundClip(Mix_Chunk *_clip)
{
	clip = _clip;
	channel = -1;
}

void SoundClip::Play()
{
	channel = Mix_PlayChannel(-1, clip, 0);
}

void SoundClip::Pause()
{
	if ( channel == -1 )
		return;

	if ( Mix_Paused(channel) )
		Mix_Resume(channel);
	else
		Mix_Pause(channel);
}

void SoundClip::Volume(int _volume)
{
	Mix_Volume(channel, _volume);
}

void SoundClip::Stop()
{
	if ( channel == -1)
		return;

	Mix_HaltChannel(channel);
	channel = -1;
}

*/