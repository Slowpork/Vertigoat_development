//MenuState.h

#pragma once
#include "State.h"
#include <string>

class System;
class ObjectManager;
class AnimatedSprite;

class MenuState : public State 
{
public:
	MenuState(System* _system);

	bool Enter();
	void Exit();
	void Pause();
	void Resume();
	bool Update(float _deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);
	bool isPaused();
	bool isBase();

private:

	std::string m_name;
	std::string m_next;
	bool m_paused;
	bool m_base;
	System* m_system;

	ObjectManager* object_manager;
	
	// STATE SPECIFIC

	AnimatedSprite* spr_background;
	AnimatedSprite* spr_title;
	AnimatedSprite* spr_candle_light;
	AnimatedSprite* spr_candle_blow;
	AnimatedSprite* spr_candle_idle;
	AnimatedSprite* spr_candle;
	

	int state;
	float brightness;
	float title_alpha;
};