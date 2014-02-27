// GameObject.h

#include "GameObject.h"
#include "AnimatedSprite.h"
#include "Collider.h"

#include <iostream>
#include <math.h>
#include "Math.h"

GameObject::GameObject(AnimatedSprite *_sprite, Collider *_collider)
{
	m_sprite = _sprite;
	m_collider = _collider;
	m_depth = 0;

	//std::cout << "  GameObject\n";
}

GameObject::~GameObject()
{
	
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

	std::cout << "  ~GameObject\n";
}

const sf::Vector2f& GameObject::getPosition() const
{
	return m_pos;
}

void GameObject::setPosition(sf::Vector2f& _pos)
{
	m_pos = _pos;

	if (hasSprite())
		m_sprite->setPosition(m_pos);

	if ( hasCollider())
		m_collider->m_pos = m_pos;
}

const int& GameObject::getDepth() const
{
	return m_depth;
}

void GameObject::setDepth(int _depth)
{
	m_depth = _depth;
}

void GameObject::turnToPoint(sf::Vector2f _point)
{
	float angle = atan2(_point.y - m_pos.y,
						_point.x - m_pos.x);
	m_sprite->setRotation(angle * (180/Math::PI));
}


bool GameObject::hasSprite()
{
	return m_sprite != nullptr;
}

AnimatedSprite* GameObject::getSprite()
{
	return m_sprite;
}

bool GameObject::hasCollider()
{
	return m_collider != nullptr;
}

Collider* GameObject::getCollider()
{
	return m_collider;
}

sf::Vector2f GameObject::getVelocity()
{
	return m_vel;
}

float GameObject::getSpeed()
{
	return m_friction;
}