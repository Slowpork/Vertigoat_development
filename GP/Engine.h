//Engine.h

#include "stdafx.h"
#pragma once


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

	float m_ticks;
};