//LoadingState.h

#pragma once
#include "State.h"
#include "stdafx.h"

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
	System* m_system;
};