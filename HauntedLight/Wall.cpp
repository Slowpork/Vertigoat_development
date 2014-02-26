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

	if (m_collider != nullptr)
	{
		if (hasCollider())
		{
			delete m_collider;
			m_collider = nullptr;
		}
	}
	
	if (m_sprite != nullptr)
	{
		if (hasSprite())
		{
			delete m_sprite;
			m_sprite = nullptr;
		}
	}
}