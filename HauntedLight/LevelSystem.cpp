// LevelSystem.cpp

#include "LevelSystem.h"

#include "ObjectManager.h"
#include "SpriteManager.h"

#include "AnimatedSprite.h"
#include "Collider.h"

#include "Wall.h"

/*

	m_status RULES

	0 = Ignore.
	1 = Generate.
	2 = 


*/

LevelSystem::LevelSystem(ObjectManager* _object_manager, SpriteManager* _sprite_manager)
{
	m_object_manager = _object_manager;
	m_sprite_manager = _sprite_manager;

	// reset status
	for(int X = 0; X < WIDTH; X++)
	{
		for(int Y = 0; Y < HEIGHT; Y++)
			m_status[X][Y] = 0;
	}

	m_player_pos = sf::Vector2f(0.f, 0.f);
	m_enemy_pos = sf::Vector2f(0.f, 0.f);
}

bool LevelSystem::atPosition(sf::Vector2f _pos)
{
	return ( m_object_manager->atPosition(_pos) != -1 ? true : false);
}

void LevelSystem::addWall(sf::Vector2f _pos)
{
	AnimatedSprite* spr_wall = m_sprite_manager->getSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall* wall = new Wall(spr_wall,col_wall);
	wall->setPosition(_pos);
	m_object_manager->Add(wall,5);
}

void LevelSystem::setPlayerPos(sf::Vector2f _pos)
{
	m_player_pos = _pos;
}

void LevelSystem::setEnemyPos(sf::Vector2f _pos)
{
	m_enemy_pos = _pos;
}

bool LevelSystem::genCorridor(int _x, int _y, int _length, int _direction)
{
	return true;
}

bool LevelSystem::genRoom(int _x, int _y, int _width, int _height, int _direction)
{
	return true;
}

void LevelSystem::Update()
{

}