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
		"spr_wall_brick.png",0,0,128,128,16);
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
	/*
	if ( Random::between(1,3) == 1 )
	{
		std::cout << std::endl;
	}*/
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
		//std::cout << "X: " << PlayerX << " Y: " << PlayerY << std::endl;
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

// #################################################################### PATH FINDING
bool LevelSystem::Passable( int nx, int ny )
{
	if (    nx >= 0 && nx < WIDTH 
			&& ny >= 0 && ny < HEIGHT )
	{
		return (m_object_manager->atPosition(sf::Vector2f(nx*SIZE, ny*SIZE)) == -1 );
		/*
		int index = ny*WIDTH+nx;
		char c = gMap[ index ];
		if ( c == ' ' )
			return 1;
		else if ( c == 'D' )
			return 2;*/
	}		
	return 0;

}

void LevelSystem::NodeToXY( void* node, int* x, int* y ) 
{
	int index = (int)node;
	*y = index / WIDTH;
	*x = index - *y * WIDTH;
}

void* LevelSystem::XYToNode( int x, int y )
{
	return (void*) ( y*WIDTH + x );
}

float LevelSystem::LeastCostEstimate( void* nodeStart, void* nodeEnd ) 
{
	int xStart, yStart, xEnd, yEnd;
	NodeToXY( nodeStart, &xStart, &yStart );
	NodeToXY( nodeEnd, &xEnd, &yEnd );

	/* Compute the minimum path cost using distance measurement. It is possible
		to compute the exact minimum path using the fact that you can move only 
		on a straight line or on a diagonal, and this will yield a better result.
	*/
	int dx = xStart - xEnd;
	int dy = yStart - yEnd;
	return (float) sqrt( (double)(dx*dx) + (double)(dy*dy) );
}

void LevelSystem::AdjacentCost( void* node, std::vector< micropather::StateCost > *neighbors ) 
{
	int x, y;
	const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };

	NodeToXY( node, &x, &y );

	for( int i=0; i<8; ++i ) 
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if ( Passable( nx, ny ) )
		{
			// Normal floor
			micropather::StateCost nodeCost = { XYToNode( nx, ny ), cost[i] };
			neighbors->push_back( nodeCost );
		}
		else 
		{
			// Normal floor
			micropather::StateCost nodeCost = { XYToNode( nx, ny ), FLT_MAX };
			neighbors->push_back( nodeCost );
		}
	}
}

void LevelSystem::PrintStateInfo( void* node )
{
	int x, y;
	NodeToXY( node, &x, &y );
	printf( "(%d,%d)", x, y );
}