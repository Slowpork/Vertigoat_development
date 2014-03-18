//Engine.h


#pragma once
#include "StateManager.h"

class StateManager;
class System;
class AnimatedSprite;

class Engine
{
public:
	Engine();
	//~Engine();

	bool Init();

	void Run();
	void Cleanup();

private:
	void updateEvents();
	void updateDeltatime();

	System* m_system;
	StateManager m_state_manager;

	AnimatedSprite* spr_cursor;
	AnimatedSprite* spr_sight;

	bool m_running;
	float m_deltatime;
	float m_fps;

	float m_ticks;
};