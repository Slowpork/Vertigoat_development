// Wall.cpp

#include "Wall.h"

#include <iostream>

#include "SFML\Graphics\RenderWindow.hpp"
#include "AnimatedSprite.h"

Wall::Wall(AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_health = 5;
}

bool Wall::hit()
{
	m_health--;
	//spr_cracks->setFrame(5 - m_health);
	return m_health < 1;
}

void Wall::drawCracks(sf::RenderWindow* _window)
{
	_window->draw(*spr_cracks);
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