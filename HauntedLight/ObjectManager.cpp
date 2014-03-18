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
	for(auto& object: m_objects)
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

	// FIX PROXIMITY TILING
	proximityTiling(ID, _object);
}

void ObjectManager::destroy(int _ID)
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

		proximityTiling(_ID, temp_obj);
		delete temp_obj;

		return;
	}
	std::cout << _ID << " Does not exist!" << std::endl;
}

void ObjectManager::proximityTiling(int _ID, GameObject* _object)
{
	//std::cout << "--------------------\n" << std::endl;
	int temp_ID = -1;
	for(float X = _object->getPosition().x - 128.f; X <= _object->getPosition().x + 128.f; X += 128.f)
	{
		for(float Y = _object->getPosition().y - 128.f; Y <= _object->getPosition().y + 128.f; Y += 128.f)
		{
			temp_ID = atPosition(sf::Vector2f(X + 64.f,Y + 64.f));
			if (temp_ID != -1 && temp_ID != _ID)
			{
				tile(temp_ID);
				//std::cout << "ID: " << temp_ID << std::endl;
			}
		}
	}
}

bool ObjectManager::CheckDirection(float _x, float _y, int _dir)
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
	//std::cout << "woo?" << std::endl;
	return false;
}

void ObjectManager::tile(int _ID)
{
	int image_index = 0;
	GameObject* obj = getObject(_ID);
	sf::Vector2f objPos = obj->getPosition();

	//std::cout << "pos X: " << objPos.x << " Y: " << objPos.y << std::endl;

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

	//image_index -= 1;

	//std::cout << image_index << std::endl;

	obj->getSprite()->setFrame(image_index);
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

bool ObjectManager::pointInside(sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _point)
{
	return (_point.x > _pos.x && _point.x < _pos.x + _size.x &&
	   _point.y > _pos.y && _point.y < _pos.y + _size.y);
}

void ObjectManager::Draw(sf::RenderWindow* _window, float _alpha)
{
	sf::Vector2f pos(_window->getView().getCenter().x - _window->getSize().x/2,
					 _window->getView().getCenter().y - _window->getSize().y/2);
	sf::Vector2f size(_window->getSize().x,_window->getSize().y);

	for(int z = m_min_z; z <= m_max_z; z++)
	{
		for(auto& object: m_objects)
		{
			/*if (!pointInside(pos,size,object.second->getPosition()) )
				continue;*/

			if (object.second->getDepth() == z && object.second->hasSprite())
			{
				//std::cout << object.depth << std::endl;
				object.second->getSprite()->setColor(sf::Color((int)_alpha,(int)_alpha,(int)_alpha,255));
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