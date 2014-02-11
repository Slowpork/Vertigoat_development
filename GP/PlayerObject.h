// PlayerObject.h

#pragma once
#include "stdafx.h"
#include "SFML/System/Vector2.hpp"

class PlayerObject : public GameObject
{
public:
	PlayerObject(Keyboard* _keyboard, Mouse* _mouse);

	void Update(float _deltatime);
private:

private:
	Keyboard* m_keyboard;
	Mouse* m_mouse;

	sf::Vector2f m_max_vel;
};