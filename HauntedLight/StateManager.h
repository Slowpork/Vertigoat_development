//Statemanager.h

#pragma once
#include <string>
#include <vector>
#include <stack>

class State;
class System;

class StateManager {
	friend class Engine;
public:
	StateManager();
	~StateManager();

	void Attach(State* state);
	void SetState(const std::string &type);

	void Update(float deltatime);
	void Draw();
	
	bool isState(std::string _state);
	void ChangeState();
	void PauseState();
	bool IsRunning();

private:


private:
	std::vector<State*> m_states;
	std::vector<State*> m_current;
	//State* m_current;
};
