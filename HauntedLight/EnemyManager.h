// EnemyManager.h

#pragma once

#include <map>
#include <SFML\System\Vector2.hpp>
#include "EnemyObject.h"

namespace sf
{
	class RenderWindow;
};

class GameObject;

class EnemyManager
{
	friend class CollisionManager;
public:

	EnemyManager();
	~EnemyManager();

	void Add(GameObject* _object);
	void destroy(int _ID);
	void Update(float _deltatime, sf::Vector2f _playerpos);
	void Draw(sf::RenderWindow* _window);

private:


private:

	std::map<int,GameObject*> m_objects;
	static int ID;
};