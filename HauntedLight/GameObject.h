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

	const int& getDepth() const;
	void setDepth(int _depth);

	void addSprite(AnimatedSprite* _spritealt);
	bool hasSprite();
	AnimatedSprite* getSprite();

	bool hasCollider();
	Collider* getCollider();

	sf::Vector2f getVelocity();

	float getSpeed();

protected:

	void turnToPoint(sf::Vector2f _point, float _speed = 0.f);

protected:

	AnimatedSprite* m_sprite;
	AnimatedSprite* m_sprite_alt;
	Collider* m_collider;

	bool alt_sprite;

	float m_friction;
	float m_min_friction;
	float m_max_friction;

	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	int m_depth;
};