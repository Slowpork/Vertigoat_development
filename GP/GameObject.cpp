// GameObject.h

#include "stdafx.h"
#include "GameObject.h"

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