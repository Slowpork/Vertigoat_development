//GameState.h

#pragma once
#include "State.h"
#include <string>

#include "SFML\System\Vector2.hpp"

class System;
class ObjectManager;
class PlayerObject;
class CollisionManager;
class LightSystem;
class AnimatedSprite;


namespace sf
{
	class Sound;
	class Music;
	class Font;
};

class GameState : public State {
public:
	GameState(System* _system);

	bool Enter();
	void Exit();
	void Pause();
	void Resume();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);
	bool isPaused();
	bool isBase();

private:

	void addWall(sf::Vector2f _pos);
	void viewScale(float _deltatime);
	void FlickerLight(float _deltatime);
	void playerCollision();
	void drawFloor();

private:

	// STATE VARIABLES
	std::string m_name;
	std::string m_next;
	bool m_paused;
	bool m_base;
	System* m_system;
	
	// SYSTEMS
	
	float m_timer;

	ObjectManager* m_object_manager;
	CollisionManager* m_collision_manager;
	LightSystem* m_light_system;

	// OBJECTS
	PlayerObject* player;
	AnimatedSprite* spr_cursor;
	AnimatedSprite* spr_darkness;
	AnimatedSprite* spr_floor;
	AnimatedSprite* spr_matches_hud;

	// SOUNDS
	sf::Sound* snd_thud;
	sf::Music* music_main;

	// FONTS
	sf::Font* fnt_small;

	// VARIABLES
	float m_view_beat;
};