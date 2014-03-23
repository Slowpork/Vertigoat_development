//GameState.h

#pragma once
#include "State.h"
#include <string>

#include "SFML\System\Vector2.hpp"

class System;
class ObjectManager;
class EnemyManager;
class PickupManager;
class PlayerObject;
class PickaxeObject;
class MatchesObject;
class CollisionManager;
class LightSystem;
class AnimatedSprite;
class LevelSystem;

namespace sf
{
	class Sound;
	class Music;
	class Listener;
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

	bool LoadLevel(const std::string _filename);
	void addWall(sf::Vector2f _pos, int _depth);
	void addCrawler(sf::Vector2f _pos);
	void addCritter(sf::Vector2f _pos);
	void addPickup(sf::Vector2f _pos, int _obj);
	void viewScale(float _deltatime);
	void FlickerLight(float _deltatime);
	float LightFactor();
	void playerCollision();
	void pickupCollision();
	bool enemyCollision();
	void drawFloor();
	sf::Vector2f getSide(sf::Vector2f _pos);

private:

	// STATE VARIABLES
	std::string m_name;
	std::string m_next;
	bool m_paused;
	bool m_base;
	System* m_system;
	
	// SYSTEMS
	float m_timer;
	float m_highscore;

	float m_ui_alpha;
	float WIDTH;
	float HEIGHT;

	sf::Vector2f m_crawler_pos;

	bool m_light_updated;

	ObjectManager* m_object_manager;
	EnemyManager* m_enemy_manager;
	PickupManager* m_pickup_manager;
	CollisionManager* m_collision_manager;
	LightSystem* m_light_system;
	LevelSystem* m_level_system;

	// OBJECTS
	PlayerObject* player;
	PickaxeObject* pickaxe;
	MatchesObject* matches;
	AnimatedSprite* spr_cursor;
	AnimatedSprite* spr_darkness;
	AnimatedSprite* spr_floor;
	AnimatedSprite* spr_matches_hud;
	AnimatedSprite* spr_pickaxe_hud;
	AnimatedSprite* spr_player_shadow;

	bool critter_spawned;

	// SOUNDS
	sf::Listener* m_listener;

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
	sf::Sound* snd_pickaxe_pickup;
	
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

	// VARIABLES
	float m_view_beat;
};