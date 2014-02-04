//MenuState.h

#pragma once

#include "State.h"
#include "stdafx.h"


class Engine;

class MenuState : public State {
public:
	MenuState();

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