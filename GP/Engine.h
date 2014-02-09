//Engine.h

#pragma once
#include "stdafx.h"

class StateManager;

namespace sf 
{
	class Clock;
	class Keyboard;
	class RenderWindow;
}

class Engine
{
public:
	Engine();
	//~Engine();

	bool Init();

	void runGame();
	void Cleanup();

protected:
	void updateEvents();
	void updateDeltatime();


//	Keyboard m_keyboard;
	Engine* m_engine;
	StateManager state_manager;
	struct sf::RenderWindow* window;
	sf::Keyboard *keyboard;

	bool m_running;
	float m_deltatime;

	float m_ticks;

	sf::Clock *clock;
};