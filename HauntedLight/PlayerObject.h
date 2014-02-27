// PlayerObject.h

#pragma once
#include "SFML/System/Vector2.hpp"

#include "GameObject.h"
#include <string>

class KeyboardObject;
class MouseObject;

class PlayerObject : public GameObject
{
public:
	PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse, 
		AnimatedSprite* _sprite = nullptr, Collider* _collider = nullptr);
	~PlayerObject();

	void Update(float _deltatime);
	
	void setVelocity(sf::Vector2f _vel);
	void doFriction();

	void setSprites(AnimatedSprite* _idle, AnimatedSprite* _run);

	const float getHealth();
	const float getStamina();
	const float getMatches();
	const float getLight();
	const bool hasCandle();
private:

	void setState(std::string _state);
	void updateLight(float _deltatime);

private:
	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;

	AnimatedSprite* m_spr_run;
	AnimatedSprite* m_spr_walk;
	AnimatedSprite* m_spr_idle;

	bool m_running;

	sf::Vector2f m_max_vel;
	float m_health;
	float m_stamina;
	float m_matches;

	float m_light;
	bool m_candle;
};