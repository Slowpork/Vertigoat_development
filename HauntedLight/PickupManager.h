//PickupManager.h

#pragma once

#include "SFML/System/Vector2.hpp"
#include "PickupManager.h"
#include <vector>
#include <map>

namespace sf
{
	class RenderWindow;
};

class GameObject;

class PickupManager
{
	friend class State;

	friend class CollisionManager;
	friend class LightSystem;
public:
	PickupManager();

	void Cleanup();

	void Add(GameObject* _object);


	void Draw(sf::RenderWindow* _window, float _alpha = 255);

	int CheckCollision(GameObject* _object, sf::Vector2f& _offset);

	int atPosition(sf::Vector2f _pos);

	GameObject* getObject(int _ID);

	void destroy(int _ID);

	int getObjects();

private:
	bool pointInside(sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _point);
	bool CheckDirection(float _x, float _y, int _dir);

private:
	std::map<int,GameObject*> m_objects;


	static int ID;

private:
};

