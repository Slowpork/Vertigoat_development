// ObjectManager.cpp

#include "ObjectManager.h"
#include <algorithm>

#include "SFML\Graphics\RenderWindow.hpp"

#include "AnimatedSprite.h"
#include "Wall.h"

#include <iostream>

int ObjectManager::ID = 0;

ObjectManager::ObjectManager()
{
	m_min_z = 0;
	m_max_z = 0;
}

void ObjectManager::Cleanup()
{
	for(auto object: m_objects)
	{
		delete object.second;
		object.second = nullptr;
	}
}

void ObjectManager::Add(GameObject* _object, int _depth)
{
	_object->setDepth(_depth);
	ID++;
	m_objects.insert( std::pair<int, GameObject*>(ID, _object));
	tile(ID);
}

bool ObjectManager::CheckDirection(float _x, float _y, int _dir)
{
	switch(_dir)
	{
	case 0:
		if ( atPosition(sf::Vector2f(_x + 64.f, _y - 64.f)) )
			return true;
	break;
	case 1:
		if ( atPosition(sf::Vector2f(_x + 64.f, _y + 64.f)) )
			return true;
	break;
	case 2:
		if ( atPosition(sf::Vector2f(_x + 64.f, _y + 64.f + 128.f)) )
			return true;
	break;
	case 3:
		if ( atPosition(sf::Vector2f(_x - 64.f, _y + 64.f)) )
			return true;
	break;
	}

	return false;
}

void ObjectManager::tile(int _ID)
{
	int image_index = 0;
	GameObject* obj = getObject(_ID);
	sf::Vector2f objPos = obj->getPosition();

	if (!CheckDirection(objPos.x, objPos.y, 1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0) )
	{
		image_index = 0;
	}
	// 1
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0) )
	{
		image_index = 1;
	}
	// 2
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 2;
	}
	// 3
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 3;
	}
	// 4
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 4;
	}
	// 5
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 5;
	}
	// 6
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 6;
	}
	// 7
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 7;
	}
	// 8
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 8;
	}
	// 9
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 9;
	}
	// 10 Hor
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 10;
	}
	// 11 Vert
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 11;
	}
	// 12 vänster
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 12;
	}
	// 13 ner
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 13;
	}
	// 14 vänster
	else if (CheckDirection(objPos.x, objPos.y,1)
	&& !CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 14;
	}
	// 15 upp
	else if (!CheckDirection(objPos.x, objPos.y,1)
	&& CheckDirection(objPos.x, objPos.y,2)
	&& !CheckDirection(objPos.x, objPos.y,3)
	&& !CheckDirection(objPos.x, objPos.y,0))
	{
		image_index = 15;
	}

	image_index = 0;

	obj->getSprite()->setFrame(image_index);
}

void ObjectManager::destroy(int _ID)
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

GameObject* ObjectManager::getObject(int _ID)
{
	std::map<int, GameObject*>::iterator pos = m_objects.find(_ID);

	if (pos != m_objects.end())
		return pos->second;
	return nullptr;
}

int ObjectManager::getObjects()
{
	return m_objects.size();
}

int ObjectManager::atPosition(sf::Vector2f _pos)
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

bool ObjectManager::setActiveDepth(int _min, int _max)
{
	if ( _max < _min)
		return false;
	else
	{
		m_min_z = _min;
		m_max_z = _max;
	}

	return true;
}

void ObjectManager::Draw(sf::RenderWindow* _window, float _alpha)
{
	for(int z = m_min_z; z <= m_max_z; z++)
	{
		for(auto& object: m_objects)
		{
			if (object.second->getDepth() == z && object.second->hasSprite())
			{
				//std::cout << object.depth << std::endl;
				object.second->getSprite()->setColor(sf::Color(_alpha,_alpha,_alpha,255));
				_window->draw(*object.second->getSprite());

				if (z == 5){
					//static_cast<Wall*> (object.second)->drawCracks(_window);
				}
			}
		}
	}
}

void CheckCollision(GameObject* _object, sf::Vector2f& _offset)
{

}