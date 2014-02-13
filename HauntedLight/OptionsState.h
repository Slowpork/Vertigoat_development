//OptionsState.h

#pragma once
#include "State.h"
#include <string>

class System;
class ObjectManager;

class OptionsState : public State {
public:
	OptionsState(System* _system);

	bool Enter();
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:

	std::string m_name;
	std::string m_next;

	bool m_done;
	System* m_system;

	ObjectManager* object_manager;
};