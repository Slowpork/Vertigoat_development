//GameState.h

#pragma once
#include "stdafx.h"
#include "State.h"

namespace sf
{
	class Sprite;
};

class System;
class ObjectManager;
class PlayerObject;

class GameState : public State {
public:
	GameState(System* _system);

	bool Enter();
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:
	void viewBeat(float _deltatime);

private:

	// STATE VARIABLES
	std::string m_name;
	std::string m_next;
	
	// SYSTEMS
	System* m_system;

	ObjectManager* m_object_manager;
	CollisionManager* m_collision_manager;
	//LightSystem* light_system;

	// OBJECTS
	PlayerObject* player;
	sf::Sprite* spr_cursor;
	sf::Sprite* spr_darkness;

	// VARIABLES
	bool m_done;
	float m_view_beat;
};