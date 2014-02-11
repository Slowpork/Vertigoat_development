//MenuState.h

#pragma once
#include "stdafx.h"
#include "SFML/System/Vector2.hpp"

class System;

class MenuState : public State 
{
public:
	MenuState(System* _system);

	bool Enter();
	void Exit();
	bool Update(float _deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:
	bool m_done;
	std::string m_next_state;
	System* m_system;

	ObjectManager* object_manager;

	sf::Vector2f pos;
};