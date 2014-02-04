//OptionsState.h

#pragma once

#include "State.h"
#include <string>
#include "stdafx.h"

class Engine;

class OptionsState : public State {
public:
	OptionsState();

	bool Enter(Engine* engine);
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:
	bool m_done;
	std::string m_next_state;
	Engine* m_engine;
};