// ObjectManager.h

#pragma once

#include "SFML/System/Vector2.hpp"
#include "GameObject.h"
#include <vector>
#include <map>

namespace sf
{
	class RenderWindow;
};

class GameObject;

class ObjectManager
{
	friend class State;

	friend class CollisionManager;
	friend class LightSystem;
public:
	ObjectManager();

	void Cleanup();

	void Add(GameObject* _object, int _depth);

	void tile(int _ID);
	
	bool setActiveDepth(int _min, int _max);

	void Draw(sf::RenderWindow* _window, float _alpha = 255);

	void CheckCollision(GameObject* _object, sf::Vector2f& _offset);

	int atPosition(sf::Vector2f _pos);

	GameObject* getObject(int _ID);

	void destroy(int _ID);

	int getObjects();

private:
	bool pointInside(sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _point);
	void proximityTiling(int _ID, GameObject* _object);
	bool CheckDirection(float _x, float _y, int _dir);

private:
	std::map<int,GameObject*> m_objects;

	int m_max_z;
	int m_min_z;

	static int ID;

private:
};