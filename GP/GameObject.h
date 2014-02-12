// GameObject.h

#pragma once
#include "stdafx.h"
#include "SFML/System/Vector2.hpp"

namespace sf
{
	class Sprite;
};

class Collider;

class GameObject
{
	friend class CollisionManager;
public:

	GameObject(sf::Sprite *_sprite = nullptr, Collider *_collider = nullptr);

	const sf::Vector2f& getPosition() const;
	
	void setPosition(sf::Vector2f& _pos);

	bool hasSprite();
	sf::Sprite* getSprite();

	bool hasCollider();
	Collider* getCollider();
protected:

	sf::Sprite* m_sprite;
	Collider* m_collider;

	float m_friction;

	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
};