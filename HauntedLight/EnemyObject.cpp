//EnemyObject.cpp

#pragma region Includes
#include "EnemyObject.h"

#include <SFML\Graphics\Sprite.hpp>
#include "Collider.h"
#pragma endregion

<<<<<<< HEAD
<<<<<<< HEAD
EnemyObject::EnemyObject(AnimatedSprite* _sprite, Collider* _collider) : GameObject()
=======
EnemyObject::EnemyObject(sf::Sprite* _sprite, Collider* _collider) 
	: GameObject(_sprite, _collider)
>>>>>>> cf91b77fdaac23df56d3a90d3acef55bb7740f3f
=======
EnemyObject::EnemyObject(sf::Sprite* _sprite, Collider* _collider) 
	: GameObject(_sprite, _collider)
>>>>>>> cf91b77fdaac23df56d3a90d3acef55bb7740f3f
{
	m_vel = sf::Vector2f(0.f,0.f);

	m_friction = 0.98f;

	m_sprite->setOrigin(m_sprite->getLocalBounds().width/2,
		m_sprite->getLocalBounds().height/2);
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