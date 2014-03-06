// LevelSystem.cpp

#include "LevelSystem.h"
#include "Math.h"

#include "ObjectManager.h"
#include "SpriteManager.h"

#include "AnimatedSprite.h"
#include "Collider.h"

#include "Wall.h"

#include <iostream>
#include "Random.h"

/*

	m_status RULES
	
   -1 = Ignore
    This tile have already been generated.

	0 = Ignore
	The player is currently on this tile

	1 = Generate
	The player has been here and you need to generate it (again)


*/

LevelSystem::LevelSystem(ObjectManager* _object_manager, SpriteManager* _sprite_manager)
{
	m_object_manager = _object_manager;
	m_sprite_manager = _sprite_manager;

	

	// reset status
	for(int X = 0; X < WIDTH; X++)
	{
		for(int Y = 0; Y < HEIGHT; Y++)
		{
			m_status[X][Y] = -1;
		}
	}

	std::cout << "DONE" << std::endl;

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

	m_player_pos.x = m_player_pos.x - ((int)m_player_pos.x % SIZE );
	m_player_pos.y = m_player_pos.y - ((int)m_player_pos.y % SIZE );

	m_player_pos.x /= SIZE;
	m_player_pos.y /= SIZE;
}

void LevelSystem::setEnemyPos(sf::Vector2f _pos)
{
	m_enemy_pos = _pos;

	m_enemy_pos.x = m_enemy_pos.x - ((int)m_enemy_pos.x % SIZE );
	m_enemy_pos.y = m_enemy_pos.y - ((int)m_enemy_pos.y % SIZE );

	m_enemy_pos.x /= SIZE;
	m_enemy_pos.y /= SIZE;
}

void LevelSystem::generate(int _x, int _y)
{
	std::cout << "Generate X:" << _x << " Y: " << _y << std::endl;

	if ( Random::between(1,3) == 1 )
	{
		std::cout << std::endl;
	}
}

bool LevelSystem::genCorridor(int _x, int _y, int _length, int _direction)
{
	return true;
}

bool LevelSystem::genRoom(int _x, int _y, int _width, int _height, int _direction)
{
	return true;
}

void LevelSystem::Update(sf::Vector2f _player, sf::Vector2f _enemy)
{
	setPlayerPos(_player);
	setEnemyPos(_enemy);

	int PlayerX = (int)m_player_pos.x;
	int PlayerY = (int)m_player_pos.y;

	

	if (PlayerX > WIDTH || PlayerX < 0 || PlayerY < 0 || PlayerY > HEIGHT)
	{
		std::cout << "  ERROR: out of bounds!" << std::endl;
		return;
	}
	else
	{
		std::cout << "X: " << PlayerX << " Y: " << PlayerY << std::endl;
	}

	//std::cout << "BEGIN" << std::endl;

	
	// RESET PREVIOUS PLAYER POSITION
	for(int X = PlayerX - 1; X < PlayerX + 1; X++)
	{
		for(int Y = PlayerY - 1; Y < PlayerY + 1; Y++)
		{
			if (X < WIDTH || X > 0 || Y > 0 || Y < HEIGHT) // Out of bounds
			{
				if (m_status[X][Y] == 0 )
				{
					if (X != PlayerX && Y != PlayerY)
					m_status[X][Y] = 1;
				}
			}
		}
	}

	//std::cout << "DONE" << std::endl;

	// PLAYER IS HERE
	m_status[PlayerX][PlayerY] = 0;

	for(int X = m_player_pos.x - 1; X < m_player_pos.x + 1; X++)
	{
		for(int Y = m_player_pos.y - 1; Y < m_player_pos.y + 1; Y++)
		{
			if (X < WIDTH || X > 0 || Y > 0 || Y < HEIGHT) // Out of bounds
			{
				if (m_status[X][Y] == 1) // GENERATE
				{
					generate(X,Y);
					m_status[X][Y] = -1; // Generation done
				}
			}
		}
	}
}