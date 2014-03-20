//EnemyObject.h
#pragma once

#include <SFML\System\Vector2.hpp>

#include "GameObject.h"

namespace sf
{
	class RenderWindow;
};

class EnemyObject : public GameObject
{
public:
	EnemyObject(AnimatedSprite* _sprite = nullptr, Collider* _collider = nullptr);

	virtual void Update(float _deltatime, sf::Vector2f _playerpos) = 0;
	virtual void Draw(sf::RenderWindow* _window) = 0;

	void setVelocity(sf::Vector2f _vel);
	void doFriction();
	void setHealth(float _health);
private:

private:
	float m_health;
};

