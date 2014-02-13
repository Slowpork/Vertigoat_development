// ObjectManager.h

#pragma once

#include "SFML/System/Vector2.hpp"
#include "GameObject.h"
#include <vector>

namespace sf
{
	class RenderWindow;
};

class GameObject;

struct Objects
{
	GameObject obj;
	int depth;
};

class ObjectManager
{
	friend class State;

	friend class CollisionManager;

	friend class GameState;
	friend class LoadingState;
	friend class MenuState;
	friend class OptionsState;
public:
	ObjectManager();

	void Cleanup();

	void Add(GameObject& _object, int _depth);
	
	bool setActiveDepth(int _min, int _max);

	void Draw(sf::RenderWindow* _window);

	void CheckCollision(GameObject* _object, sf::Vector2f& _offset);

	Objects* atPosition(sf::Vector2f _pos);

	void destroy(Objects* _obj);

private:
	std::vector<Objects> m_objects;

	int m_max_z;
	int m_min_z;

private:
};