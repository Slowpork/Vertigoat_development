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

	//friend class GameState;
	friend class LoadingState;
	friend class MenuState;
	friend class OptionsState;
public:
	ObjectManager();

	void Cleanup();

	void Add(GameObject* _object, int _depth);
	
	bool setActiveDepth(int _min, int _max);

	void Draw(sf::RenderWindow* _window);

	void CheckCollision(GameObject* _object, sf::Vector2f& _offset);

	int atPosition(sf::Vector2f _pos);

	void destroy(int _ID);

	int getObjects();

private:
	std::map<int,GameObject> m_objects;

	int m_max_z;
	int m_min_z;

	static int ID;

private:
};