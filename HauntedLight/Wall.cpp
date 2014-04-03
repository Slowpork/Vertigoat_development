// Wall.cpp

#include "Wall.h"

#include <iostream>

#include "SFML\Graphics\RenderWindow.hpp"
#include "AnimatedSprite.h"
#include "Collider.h"

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

	int side = 0;

	if (_side.x > 0)
		side = 1;
	if (_side.x < 0)
		side = 3;
	if (_side.y > 0)
		side = 2;
	if (_side.y < 0)
		side = 0;

	side--;

	if (side < 0)
		side = 3;

	m_health -= (spr_cracks[side]->getFrame() + 1)*0.1;

	/*
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
		m_health = 4;*/

	spr_cracks[side]->setFrame(5 - m_health);
	return m_health < 1;
}

void Wall::setCracks(AnimatedSprite* _sprite, int _index)
{
	spr_cracks[_index] = _sprite;
	spr_cracks[_index]->setRotation(90*_index);
	//spr_cracks[_index]->setFrame(4);
	spr_cracks[_index]->setPosition(sf::Vector2f(getPosition().x + 64.f,getPosition().y + 64.f));
}

void Wall::drawCracks(sf::RenderWindow* _window)
{
	for(unsigned int i = 0; i < 4; i++)
	_window->draw(*spr_cracks[i]);
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