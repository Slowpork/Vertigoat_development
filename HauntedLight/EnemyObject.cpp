// EnemyObject.cpp

#include "EnemyObject.h"
#include <cmath>

EnemyObject::EnemyObject(AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_friction = 0.88f;
}

void EnemyObject::setVelocity(sf::Vector2f _vel)
{
	m_vel = _vel;
}

void EnemyObject::doFriction()
{
	m_vel *= m_friction;
}

void EnemyObject::setHealth(float _health)
{
	m_health = _health;
}

void EnemyObject::hasCollided(bool _collided)
{
	m_collided = _collided;
}

float EnemyObject::getDistance(sf::Vector2f _obj1, sf::Vector2f _obj2)
{
	float dif;
	float dify;
	float difx;

	dify = _obj2.y - _obj1.y;
	difx = _obj2.x - _obj1.x;

	dif = sqrt((dify*dify)+(difx*difx));

	return dif;
}

sf::Vector2f EnemyObject::getDirection(sf::Vector2f _obj1, sf::Vector2f _obj2)
{
	float length = getDistance(_obj1, _obj2);

	sf::Vector2f dif;

	dif.x = _obj2.x - _obj1.x;
	dif.y = _obj2.y - _obj1.y;

	sf::Vector2f dir = sf::Vector2f(dif.x/length, dif.y/length);

	return dir;
}