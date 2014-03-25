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
	
	void setVelocity(sf::Vector2f _vel);
	void doFriction();

	bool doMine(float _deltatime);

	void setSprites(AnimatedSprite* _idle, AnimatedSprite* _run, AnimatedSprite * _mine);

	bool addMatch();
	bool addPickaxe();
	void removePickaxe();
	void blowout();
	bool holdMatch();

	const float getHealth();
	void setStamina(float _value);
	const float getStamina();
	const int getMatches();
	const int getPickaxe();
	const float getLight();
	const bool hasCandle();
	void lightCandle();
private:

	void setState(std::string _state);
	void updateLight(float _deltatime);

private:
	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;

	AnimatedSprite* m_spr_run;
	AnimatedSprite* m_spr_walk;
	AnimatedSprite* m_spr_idle;
	AnimatedSprite* m_spr_mine;

	bool m_running;
	bool m_hold_match;

	sf::Vector2f m_max_vel;
	float m_health;
	float m_stamina;
	int m_matches;
	int m_pickaxe;

	float m_light;
	bool m_candle;
	bool  m_moving;
	bool m_mining;

};