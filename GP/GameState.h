//GameState.h

#pragma once

#include "stdafx.h"
#include "State.h"

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
	bool m_done;
	std::string m_next_state;
	System* m_system;

	ObjectManager* object_manager;

	PlayerObject* player;
};