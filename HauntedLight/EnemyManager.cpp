// EnemyManager.cpp

#include "EnemyManager.h"
#include "EnemyObject.h"

#include <iostream>

int EnemyManager::ID = 0;

EnemyManager::EnemyManager()
{

}

EnemyManager::~EnemyManager()
{
	for(auto& obj: m_objects)
	{
		delete obj.second;
		obj.second = nullptr;
	}
}

void EnemyManager::Add(EnemyObject* _object)
{
	ID++;
	m_objects.insert( std::pair<int, EnemyObject*>(ID, _object));
}

void EnemyManager::destroy(int _ID)
{
	std::map<int, EnemyObject*>::iterator pos = m_objects.find(_ID);

	if (pos != m_objects.end())
	{
		delete pos->second;
		pos->second = nullptr;

		m_objects.erase(pos);

		return;
	}
	std::cout << _ID << " Does not exist!" << std::endl;
}

void EnemyManager::Update(float _deltatime, sf::Vector2f _playerpos)
{
	for(auto& obj: m_objects)
	{
		obj.second->Update(_deltatime, _playerpos);
	}
}

void EnemyManager::Draw(sf::RenderWindow* _window)
{
	for(auto& obj: m_objects)
	{
		obj.second->Draw(_window);
	}
}