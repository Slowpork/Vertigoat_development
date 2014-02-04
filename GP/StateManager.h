//Statemanager.h

#pragma once

#include <vector>
#include "stdafx.h"

class State;
class Engine;

class StateManager {
	friend class Engine;
public:
	StateManager();
	~StateManager();

	void Attach(State *state);
	void Update(float deltatime);
	void Draw();

	void SetState(const std::string &type);
	void ChangeState();
	bool IsRunning();

private:
	std::vector<State*> m_states;
	State *m_current;
	Engine* engine;
};
