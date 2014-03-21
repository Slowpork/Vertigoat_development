// Wall.cpp

#include "Wall.h"

#include <iostream>

#include "SFML\Graphics\RenderWindow.hpp"
#include "AnimatedSprite.h"

Wall::Wall(AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_health = 4;
}

bool Wall::hit(sf::Vector2f _side)
{
	//std::cout << "hit X: " << _side.x << " Y: " << _side.y << std::endl;

	if (m_depth != 5)
		return false;

	float prev_rot = spr_cracks->getRotation();

	if (_side.x > 0)
		spr_cracks->setRotation(0);
	if (_side.x < 0)
		spr_cracks->setRotation(180);
	if (_side.y > 0)
		spr_cracks->setRotation(90);
	if (_side.y < 0)
		spr_cracks->setRotation(270);

	if ( spr_cracks->getRotation() == prev_rot )
		m_health--;
	else
		m_health = 4;

	spr_cracks->setFrame(5 - m_health);
	return m_health < 1;
}

void Wall::setCracks(AnimatedSprite* _sprite)
{
	spr_cracks = _sprite;
	spr_cracks->setPosition(sf::Vector2f(getPosition().x + 64.f,getPosition().y + 64.f));
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