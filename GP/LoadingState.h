//LoadingState.h

#pragma once
#include "State.h"
#include "stdafx.h"

class Engine;

class LoadingState : public State {
public:
	LoadingState();

	bool Enter(Engine* engine);
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:
	Engine* m_engine;
};