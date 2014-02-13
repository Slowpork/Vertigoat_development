// PlayerObject.h

#pragma once
#include "stdafx.h"
#include "SFML/System/Vector2.hpp"

class PlayerObject : public GameObject
{
public:
	PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse, 
		sf::Sprite* _sprite = nullptr, Collider* _collider = nullptr);

	void Update(float _deltatime);
	void setVelocity(sf::Vector2f _vel);
	void doFriction();

	float getHealth();
	float getStamina();
private:

	void turnToCursor();

private:
	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;

	sf::Vector2f m_max_vel;
	float m_health;
	float m_stamina;
};