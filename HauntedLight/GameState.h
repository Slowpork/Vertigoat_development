//GameState.h

#pragma once
#include "State.h"
#include <string>

#include "SFML\System\Vector2.hpp";

namespace sf
{
	class Sprite;
};

class System;
class ObjectManager;
class PlayerObject;
class CollisionManager;
class LightSystem;

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
	sf::Sprite* spr_cursor;
	sf::Sprite* spr_darkness;
	sf::Sprite* spr_floor;

	// VARIABLES
	bool m_done;
	float m_view_beat;
};