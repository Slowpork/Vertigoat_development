//Engine.h


#pragma once
#include "StateManager.h"

class StateManager;
class System;

class Engine
{
public:
	Engine();
	//~Engine();

	bool Init();

	void Run();
	void Cleanup();

protected:
	void updateEvents();
	void updateDeltatime();

	System* m_system;
	StateManager state_manager;

	bool m_running;
	float m_deltatime;
	float m_fps;

	float m_ticks;
};