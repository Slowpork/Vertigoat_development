//LoadingState.h

#pragma once
#include "State.h"
#include <string>

class System;
class ObjectManager;

class LoadingState : public State {
public:
	LoadingState(System* _system);

	bool Enter();
	void Exit();
	void Pause();
	void Resume();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:
	std::string m_name;
	std::string m_next;

	System* m_system;

	ObjectManager* object_manager;
};