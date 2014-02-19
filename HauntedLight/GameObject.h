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
	~GameObject();

	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f& _pos);

	const float& getDepth();
	void setDepth(int _depth);

	bool hasSprite();
	AnimatedSprite* getSprite();

	bool hasCollider();
	Collider* getCollider();

	sf::Vector2f getVelocity();
	float getSpeed();

protected:

	void turnToPoint(sf::Vector2f _point);

protected:


	AnimatedSprite* m_sprite;
	Collider* m_collider;

	float m_friction;
	float m_min_friction;
	float m_max_friction;

	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	float m_depth;
};