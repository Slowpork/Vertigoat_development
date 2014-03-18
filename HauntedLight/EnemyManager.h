// EnemyManager.h

#pragma once

#include <map>
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RenderWindow;
};

class EnemyObject;

class EnemyManager
{
public:

	EnemyManager();
	~EnemyManager();

	void Add(EnemyObject* _object);
	void destroy(int _ID);
	void Update(float _deltatime, sf::Vector2f _playerpos);
	void Draw(sf::RenderWindow* _window);

private:


private:

	std::map<int,EnemyObject*> m_objects;
	static int ID;
};