// LevelSystem.h

#pragma once

#include "SFML\System\Vector2.hpp"
#include "micropather.h"

class ObjectManager;
class SpriteManager;

class LevelSystem : public micropather::Graph
{
public:
	LevelSystem(ObjectManager* _object_manager, SpriteManager* _sprite_manager);

	void Update(sf::Vector2f _player, sf::Vector2f _enemy);

	// PATH FINDING
	std::vector<sf::Vector2f>* getPath(sf::Vector2f _pos, sf::Vector2f _dest);
	void pathReset();

private:

	// PATH FINDING
	void NodeToXY( void* node, int* x, int* y );
	void* XYToNode( int x, int y );
	std::vector<sf::Vector2f>* ConvertPath(std::vector<void*>* _path);
	bool Passable( int _x, int _y );
	sf::Vector2f NodeToCoords(void* _node);
	virtual float LeastCostEstimate( void* nodeStart, void* nodeEnd );
	virtual void AdjacentCost( void* node, std::vector< micropather::StateCost > *neighbors );
	virtual void PrintStateInfo( void* node );

	void setPlayerPos(sf::Vector2f _pos);
	void setEnemyPos(sf::Vector2f _pos);

	bool atPosition(sf::Vector2f _pos);
	void addWall(sf::Vector2f _pos);
	void generate(int _x, int _y);
	bool genCorridor( int _x, int _y, int _length, int _direction);
	bool genRoom(int _x, int _y, int _width, int _height, int _direction);

private:

	// PATH FINDING
	micropather::MicroPather* m_pather;

	ObjectManager* m_object_manager;
	SpriteManager* m_sprite_manager;

	/// CONSTANTS
	static const int WIDTH = 30;
	static const int HEIGHT = 30;

	static const int SIZE = 128;

	// GENERATION
	int m_status[HEIGHT][WIDTH];

	sf::Vector2f m_player_pos;
	sf::Vector2f m_enemy_pos;
};