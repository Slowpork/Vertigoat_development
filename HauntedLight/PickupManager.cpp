// PickupManager.cpp

#include "PickupManager.h"
#include <algorithm>

#include "SFML\Graphics\RenderWindow.hpp"

#include "AnimatedSprite.h"
#include "Wall.h"

#include <iostream>

int PickupManager::ID = 0;

PickupManager::PickupManager()
{

}

void PickupManager::Cleanup()
{
	for(auto& object: m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}
}

void PickupManager::Add(GameObject* _object)
{
	ID++;
	m_objects.insert( std::pair<int, GameObject*>(ID, _object));
}

void PickupManager::destroy(int _ID)
{
	std::map<int, GameObject*>::iterator pos = m_objects.find(_ID);

	if (pos != m_objects.end())
	{
		GameObject* temp_obj = new GameObject();
		sf::Vector2f obj_pos = pos->second->getPosition();
		temp_obj->setPosition(obj_pos);

		delete pos->second;
		pos->second = nullptr;

		m_objects.erase(pos);

		delete temp_obj;

		return;
	}
	std::cout << _ID << " Does not exist!" << std::endl;
}


bool PickupManager::CheckDirection(float _x, float _y, int _dir)
{
	switch(_dir)
	{
		case 0:
			if ( atPosition(sf::Vector2f(_x + 64.f, _y - 64.f)) != -1 )
				return true;
		break;
		case 1:
			if ( atPosition(sf::Vector2f(_x + 64.f + 128.f, _y + 64.f)) != -1 )
				return true;
		break;
		case 2:
			if ( atPosition(sf::Vector2f(_x + 64.f, _y + 64.f + 128.f)) != -1 )
				return true;
		break;
		case 3:
			if ( atPosition(sf::Vector2f(_x - 64.f, _y + 64.f)) != -1 )
				return true;
	break;
	}
	//std::cout << "WRONG?" << std::endl;
	return false;
}


GameObject* PickupManager::getObject(int _ID)
{
	std::map<int, GameObject*>::iterator pos = m_objects.find(_ID);

	if (pos != m_objects.end())
		return pos->second;
	return nullptr;
}

int PickupManager::getObjects()
{
	return m_objects.size();
}

int PickupManager::atPosition(sf::Vector2f _pos)
{
	//std::cout << "ObjectManager::atPosition()" << std::endl;
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


bool PickupManager::pointInside(sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _point)
{
	return (_point.x > _pos.x && _point.x < _pos.x + _size.x &&
	   _point.y > _pos.y && _point.y < _pos.y + _size.y);
}

void PickupManager::Draw(sf::RenderWindow* _window, float _alpha)
{
	sf::Vector2f pos(_window->getView().getCenter().x - _window->getSize().x/2,
					 _window->getView().getCenter().y - _window->getSize().y/2);
	sf::Vector2f size(_window->getSize().x,_window->getSize().y);
}

int CheckCollision(GameObject* _object, sf::Vector2f& _offset)
{

	return 5;
}
