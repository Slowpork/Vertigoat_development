// CollisionManager.h

#pragma once

#include "SFML/System/Vector2.hpp"

class Collider;
class ObjectManager;
class PickupManager;

enum Manager
{
	WALLS,
	PICKUPS,
	COUNT
};

class CollisionManager
{
	
public:
	CollisionManager(ObjectManager* _object_manager, PickupManager* _pickup_manager);

	bool checkCollision(Collider* _object, sf::Vector2f& _offset, Manager _type);
private:
	bool RectvsRect(Collider* _object, Collider* _other, sf::Vector2f& _offset);
	bool CirclevsCircle(Collider* _object, Collider* _other, sf::Vector2f& _offset);
	bool RectvsCircle(Collider* _object, Collider* _other, sf::Vector2f& _offset);

	ObjectManager* m_object_manager;
	PickupManager* m_pickup_manager;
};