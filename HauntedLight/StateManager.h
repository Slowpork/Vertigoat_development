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
	void setMain(const std::string _main);
	void ChangeState();
	void PauseState();
	bool IsRunning();

private:
	std::vector<State*> m_states;
	State* m_current;
	State* m_main;
};
