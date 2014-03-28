// EnemyManager.h

#pragma once

#include <map>
#include <SFML\System\Vector2.hpp>
#include "EnemyObject.h"

namespace sf
{
	class RenderWindow;
};

class LevelSystem;
class GameObject;

class EnemyManager
{
	friend class CollisionManager;
public:

	EnemyManager(LevelSystem* _level_manager);
	~EnemyManager();

	void Add(GameObject* _object);
	void destroy(int _ID);
	GameObject* getObject(int _ID);
	void Update(float _deltatime, sf::Vector2f _playerpos);
	void Draw(sf::RenderWindow* _window);
	sf::Vector2f getCrawlerPos();
	void incCrawlerSpeed();

private:
	sf::Vector2f Snap(sf::Vector2f _value);
	void AlligntoWall(int _ID);
	int atPosition(sf::Vector2f _pos);

private:

	std::map<int,GameObject*> m_objects;
	sf::Vector2f crawler_pos;
	bool crawler_update;
	static int ID;

	LevelSystem* m_level_manager;
};