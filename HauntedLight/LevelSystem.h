// LevelSystem.h

#pragma once

#include "SFML\System\Vector2.hpp"

class ObjectManager;
class SpriteManager;

class LevelSystem
{
public:
	LevelSystem(ObjectManager* _object_manager, SpriteManager* _sprite_manager);

	void Update(sf::Vector2f _player, sf::Vector2f _enemy);

private:

	void setPlayerPos(sf::Vector2f _pos);
	void setEnemyPos(sf::Vector2f _pos);

	bool atPosition(sf::Vector2f _pos);
	void addWall(sf::Vector2f _pos);
	void generate(int _x, int _y);
	bool genCorridor( int _x, int _y, int _length, int _direction);
	bool genRoom(int _x, int _y, int _width, int _height, int _direction);

private:

	ObjectManager* m_object_manager;
	SpriteManager* m_sprite_manager;

	/// CONSTANTS
	static const int HEIGHT = 7;
	static const int WIDTH = 7;

	static const int SIZE = 512;

	// GENERATION
	int m_status[HEIGHT][WIDTH];

	sf::Vector2f m_player_pos;
	sf::Vector2f m_enemy_pos;
};