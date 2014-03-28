// EnemyManager.cpp

#include "EnemyManager.h"
#include "EnemyObject.h"
#include "Collider.h"

#include "Crawler.h"

#include "LevelSystem.h"
#include "AnimatedSprite.h"

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

	/*if(ID == 2)
	{
		AlligntoWall(ID);
	}*/
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

void EnemyManager::AlligntoWall(int _ID)
{
	int rotation = 0;
	GameObject* obj = getObject(_ID);
	sf::Vector2f objPos = obj->getPosition();

	bool at[4];
	at[0] = ( atPosition(sf::Vector2f(objPos.x + 64.f, objPos.y - 64.f)) != -1 );
	at[1] = ( atPosition(sf::Vector2f(objPos.x + 64.f + 128.f, objPos.y + 64.f)) != -1 );
	at[2] = ( atPosition(sf::Vector2f(objPos.x + 64.f, objPos.y + 64.f + 128.f)) != -1 );
	at[3] = ( atPosition(sf::Vector2f(objPos.x - 64.f, objPos.y + 64.f)) != -1 );

	if      (at[0])
		rotation = 1;
	else if (at[1])
		rotation = 2;
	else if (at[2])
		rotation = 3;
	else if (at[3])
		rotation = 0;

	obj->getSprite()->rotate(rotation*90.f);
}

int EnemyManager::atPosition(sf::Vector2f _pos)
{
	for(auto& object: m_objects)
	{
		sf::Vector2f pos = object.second->getPosition();
		sf::Vector2f size = object.second->getSprite()->getSize();

		if ( _pos.x > pos.x && _pos.x < pos.x + size.x )
		{
			if ( _pos.y > pos.y && _pos.y < pos.y + size.y)
			{
				return object.first;
			}
		}
	}

	return -1;
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