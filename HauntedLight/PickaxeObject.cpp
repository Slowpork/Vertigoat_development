// Wall.cpp

#include "PickaxeObject.h"

#include <iostream>

#include "SFML\Graphics\RenderWindow.hpp"
#include "AnimatedSprite.h"

PickaxeObject::PickaxeObject(AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{

}

void PickaxeObject::Pickup()
{

	//spr_cracks->setFrame(5 - m_health);
	
}


PickaxeObject::~PickaxeObject()
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