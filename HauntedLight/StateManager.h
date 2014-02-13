//Statemanager.h

#pragma once
#include <string>
#include <vector>

class State;
class System;

class StateManager {
	friend class Engine;
public:
	StateManager();
	~StateManager();

	void Attach(State* state);
	void Update(float deltatime);
	void Draw();

	void SetState(const std::string &type);
	void ChangeState();
	bool IsRunning();

private:
	std::vector<State*> m_states;
	State* m_current;
};
