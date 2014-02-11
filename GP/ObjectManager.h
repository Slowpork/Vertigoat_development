// ObjectManager.h

#pragma once
#include "stdafx.h"
#include "SFML/System/Vector2.hpp"

namespace sf
{
	class RenderWindow;
};

class GameObject;

struct Objects
{
	GameObject* obj;
	int depth;
};

class ObjectManager
{
	friend class State;

	friend class GameState;
	friend class LoadingState;
	friend class MenuState;
	friend class OptionsState;
public:
	ObjectManager();

	void Cleanup();

	void Add(GameObject* _object, int _depth);
	void Draw(sf::RenderWindow* _window);

	void CheckCollision(GameObject* _object, sf::Vector2f& _offset);
private:
	std::vector<Objects*> m_objects;

	int m_max_z;

private:
};