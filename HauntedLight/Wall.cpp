// Wall.cpp

#include "Wall.h"

#include <iostream>

Wall::Wall(AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	
}

Wall::~Wall()
{
	std::cout << "X ";
}