//EnemyObject.h
#pragma once

#pragma region Includes
#include <SFML\System\Vector2.hpp>

#include "GameObject.h"
#pragma endregion

class EnemyObject : public GameObject
{
public:
	EnemyObject(sf::Sprite* _sprite = nullptr, Collider* _collider = nullptr);

	void Update(float _deltatime);
	void setVelocity(sf::Vector2f _vel);
	void doFriction();
	void setHealth(float _health);
	void setDistance(float _maxDistance, sf::Vector2f _obj1, sf::Vector2f _obj2);

	sf::Vector2f getDistance(sf::Vector2f _obj1, sf::Vector2f _obj2);
private:

private:
	float m_health;
};

