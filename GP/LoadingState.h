//LoadingState.h

#pragma once
#include "stdafx.h"
#include "State.h"


class System;

class LoadingState : public State {
public:
	LoadingState(System* _system);

	bool Enter();
	void Exit();
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