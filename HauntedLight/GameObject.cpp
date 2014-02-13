// GameObject.h

#include "GameObject.h"
#include "SFML\Graphics\Sprite.hpp"
#include "Collider.h"
#include "Math.h"

GameObject::GameObject(sf::Sprite *_sprite, Collider *_collider)
{
	m_sprite = _sprite;
	m_collider = _collider;
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

sf::Sprite* GameObject::getSprite()
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