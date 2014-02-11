// CollisionManager.h

#pragma once
#include "stdafx.h"
#include "SFML/System/Vector2.hpp"

class Collider;

class CollisionManager
{
public:
	bool checkCollision(Collider* _object, Collider* _other, sf::Vector2f& _offset);
private:
	bool RectvsRect(Collider* _object, Collider* _other, sf::Vector2f& _offset);
	bool CirclevsCircle(Collider* _object, Collider* _other, sf::Vector2f& _offset);
	bool RectvsCircle(Collider* _object, Collider* _other, sf::Vector2f& _offset);
};