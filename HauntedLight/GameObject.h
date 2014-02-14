// GameObject.h

#pragma once
#include "SFML/System/Vector2.hpp"

namespace sf
{
	class Sprite;
};

class Collider;
class AnimatedSprite;

class GameObject
{
	friend class CollisionManager;
public:

	GameObject(AnimatedSprite* _sprite = nullptr, Collider* _collider = nullptr);

	const sf::Vector2f& getPosition() const;
	
	void setPosition(sf::Vector2f& _pos);

	bool hasSprite();
	AnimatedSprite* getSprite();

	bool hasCollider();
	Collider* getCollider();

protected:

	void turnToPoint(sf::Vector2f _point);

protected:


	AnimatedSprite* m_sprite;
	Collider* m_collider;

	float m_friction;

	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
};