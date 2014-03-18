//GameState.h

#pragma once
#include "State.h"
#include <string>

#include "SFML\System\Vector2.hpp"

class System;
class ObjectManager;
class PickupManager;
class PlayerObject;
class CollisionManager;
class LightSystem;
class AnimatedSprite;
class LevelSystem;

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
	void addPickaxe(sf::Vector2f _pos);
	void viewScale(float _deltatime);
	void FlickerLight(float _deltatime);
	float LightFactor();
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
	PickupManager* m_pickup_manager;
	CollisionManager* m_collision_manager;
	LightSystem* m_light_system;
	LevelSystem* m_level_system;

	// OBJECTS
	PlayerObject* player;
	AnimatedSprite* spr_cursor;
	AnimatedSprite* spr_darkness;
	AnimatedSprite* spr_floor;
	AnimatedSprite* spr_matches_hud;
	AnimatedSprite* spr_player_shadow;
	AnimatedSprite* spr_monster_big;
	AnimatedSprite* spr_critter;

	bool critter_spawned;

	// SOUNDS
	sf::Music* music_main;
	sf::Music* msc_Player_breathing;
	sf::Music* msc_critter_walk;

	sf::Sound* snd_thud;
	sf::Sound* snd_Start_Up_screen;
	sf::Sound* snd_Main_Menu_blow_out_candle;
	sf::Sound* snd_ambiant_alarm;
	sf::Sound* snd_big_monster_1;
	sf::Sound* snd_big_monster_2;
	sf::Sound* snd_big_monster_3;
	sf::Sound* snd_critter_attack;
	
	sf::Sound* snd_Crunching_sound;
	sf::Sound* snd_Door;
	sf::Sound* snd_Equipment_selection;
	sf::Sound* snd_Equipment_selection_2;
	sf::Sound* snd_Game_Over_screen;
	sf::Sound* snd_Mining_not_hitting_anything;
	sf::Sound* snd_Mining_Pickaxe;
	sf::Sound* snd_Mining_with_pebbles;
	sf::Sound* snd_Pickup_Powerup;
	sf::Sound* snd_Player_dies;
	sf::Sound* snd_Player_Lighting_Candle;
	sf::Sound* snd_Player_walk_test;
	sf::Sound* snd_wall_monster_1;
	sf::Sound* snd_wall_monster_2;
	sf::Sound* snd_wall_monster_3;
	sf::Sound* snd_wall_monster_4;
	sf::Sound* snd_wall_monster_5;

	// FONTS
	sf::Font* fnt_small;

	// VARIABLES
	float m_view_beat;
};