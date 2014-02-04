//GameState.h

#pragma once

#include "stdafx.h"
#include "State.h"
#include <string>

class Engine;

class GameState : public State {
public:
	GameState();

	bool Enter(Engine* engine);
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:
	bool m_done;
	std::string m_next_state;
	Engine* m_engine;
};