//OptionsState.h

#pragma once
#include "stdafx.h"

class System;

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
	bool m_done;
	std::string m_next_state;
	System* m_system;

	ObjectManager* object_manager;
};