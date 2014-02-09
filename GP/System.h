// System.h

#pragma once
#include "stdafx.h"

namespace sf
{
	class RenderWindow;
	class Clock;
};

class System
{
	friend class Engine;
	friend class State;

	friend class GameState;
	friend class LoadingState;
	friend class MenuState;
	friend class OptionsState;
public:
	System();
	~System();

	bool Init();

private:
	
	
private:

	int m_height, m_width;
	float m_ticks;

	sf::RenderWindow* m_window;
	sf::Clock* m_clock;

	FileManager* m_file_manager;
	//SoundManager* m_sound_manager;

	Keyboard* m_keyboard;
	Mouse* m_mouse;
};