// EnemyManager.cpp

#include "EnemyManager.h"
#include "EnemyObject.h"
#include "Collider.h"

#include "Crawler.h"

#include "LevelSystem.h"

#include <iostream>

int EnemyManager::ID = 0;

EnemyManager::EnemyManager(LevelSystem* _level_manager)
{
	m_level_manager = _level_manager;
}

EnemyManager::~EnemyManager()
{
	for(auto& obj: m_objects)
	{
		delete obj.second;
		obj.second = nullptr;
	}
}

void EnemyManager::Add(GameObject* _object)
{
	ID++;
	m_objects.insert( std::pair<int, GameObject*>(ID, _object));
}

void EnemyManager::destroy(int _ID)
{
	std::map<int, GameObject*>::iterator pos = m_objects.find(_ID);

	if (pos != m_objects.end())
	{
		delete pos->second;
		pos->second = nullptr;

		m_objects.erase(pos);

		return;
	}
	std::cout << _ID << " Does not exist!" << std::endl;
}

GameObject* EnemyManager::getObject(int _ID)
{
	std::map<int, GameObject*>::iterator pos = m_objects.find(_ID);

	if (pos != m_objects.end())
		return pos->second;
	return nullptr;
}

sf::Vector2f EnemyManager::Snap(sf::Vector2f _value)
{
	return sf::Vector2f(
			floor(_value.x - ((int)_value.x % 128)),
			floor(_value.y - ((int)_value.y % 128))
			);
}

void EnemyManager::Update(float _deltatime, sf::Vector2f _playerpos)
{
	for(auto& obj: m_objects)
	{
		static_cast<EnemyObject*> (obj.second)->Update(_deltatime, _playerpos);

		// CRAWLER
		if (obj.second->getDepth() == 1)
		{
			if ( static_cast<Crawler*>(obj.second)->needPath() )
			{
				std::vector<sf::Vector2f>* path = m_level_manager->getPath(
					Snap(obj.second->getPosition()),Snap(_playerpos));

				if (path != nullptr)
					static_cast<Crawler*>(obj.second)->setPath(path);
			}
		}
	}
}

void EnemyManager::Draw(sf::RenderWindow* _window)
{
	for(auto& obj: m_objects)
	{
		static_cast<EnemyObject*> (obj.second)->Draw(_window);
	}
}