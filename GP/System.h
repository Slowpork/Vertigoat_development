// System.h

#pragma once
#include "stdafx.h"

namespace sf
{
	class RenderWindow;
	class View;
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
	sf::View* m_view;
	sf::Clock* m_clock;

	FileManager* m_file_manager;
	SpriteManager* m_sprite_manager;
	//SoundManager* m_sound_manager;

	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;
};