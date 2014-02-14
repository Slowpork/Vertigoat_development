//EnemyObject.cpp

#pragma region Includes
#include "EnemyObject.h"

#include "AnimatedSprite.h"
#include "Collider.h"
#pragma endregion

EnemyObject::EnemyObject(AnimatedSprite* _sprite, Collider* _collider) 
	: GameObject(_sprite, _collider)
{
	m_sprite = _sprite;
	m_collider = _collider;
}

void EnemyObject::Update(float _deltatime)
{

}

void EnemyObject::setVelocity(sf::Vector2f _vel)
{

}

void EnemyObject::doFriction()
{

}

void EnemyObject::setHealth(float _health)
{
	m_health = _health;
}

void EnemyObject::setDistance(float _maxDistance, sf::Vector2f _obj1, sf::Vector2f _obj2)
{
	_obj1.x = _obj2.x - _maxDistance;
	_obj1.y = _obj2.y - _maxDistance;
}

sf::Vector2f EnemyObject::getDistance(sf::Vector2f _obj1, sf::Vector2f _obj2)
{
	sf::Vector2f dif;

	dif.x = _obj2.x - _obj1.x;
	dif.y = _obj2.y - _obj1.y;

	return dif;
}