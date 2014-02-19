//GameState.h

#pragma once
#include "State.h"
#include <string>

#include "SFML\System\Vector2.hpp";

class System;
class ObjectManager;
class PlayerObject;
class CollisionManager;
class LightSystem;
class AnimatedSprite;


namespace sf
{
	class SoundBuffer;
	class Music;
	class Font;
};

class GameState : public State {
public:
	GameState(System* _system);

	bool Enter();
	void Exit();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);

private:

	void addWall(sf::Vector2f _pos);
	void viewBeat(float _deltatime);
	void drawFloor();

private:

	// STATE VARIABLES
	std::string m_name;
	std::string m_next;
	
	// SYSTEMS
	System* m_system;

	ObjectManager* m_object_manager;
	CollisionManager* m_collision_manager;
	LightSystem* m_light_system;

	// OBJECTS
	PlayerObject* player;
	AnimatedSprite* spr_cursor;
	AnimatedSprite* spr_darkness;
	AnimatedSprite* spr_floor;

	// SOUNDS
	sf::SoundBuffer* snd_thud;

	// FONTS
	sf::Font* fnt_small;

	// VARIABLES
	bool m_done;
	float m_view_beat;
};