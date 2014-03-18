// PlayerObject.h

#pragma once
#include "SFML/System/Vector2.hpp"

#include "GameObject.h"
#include <string>
#include <vector>

class KeyboardObject;
class MouseObject;
class System;


class PlayerObject : public GameObject
{
public:
	PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse, 
		AnimatedSprite* _sprite = nullptr, Collider* _collider = nullptr);
	~PlayerObject();

	void Update(float _deltatime);
	
	void setPath(std::vector<sf::Vector2f>* _path);
	void setVelocity(sf::Vector2f _vel);
	void doFriction();

	void setSprites(AnimatedSprite* _idle, AnimatedSprite* _run);

	const float getHealth();
	const float getStamina();
	const int getMatches();
	const float getLight();
	const bool hasCandle();
private:

	void setState(std::string _state);
	void updateLight(float _deltatime);

private:
	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;

	std::vector<sf::Vector2f>* m_path;
	int m_current_node;

	AnimatedSprite* m_spr_run;
	AnimatedSprite* m_spr_walk;
	AnimatedSprite* m_spr_idle;

	System* m_system;


	bool m_running;

	sf::Vector2f m_max_vel;
	float m_health;
	float m_stamina;
	int m_matches;

	float m_light;
	bool m_candle;
	bool  m_moving;

	bool m_breathing;

};