// ObjectManager.cpp

#include "ObjectManager.h"
#include <algorithm>

#include "SFML\Graphics\RenderWindow.hpp"

#include "AnimatedSprite.h"

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
		delete &object;
		object.second = nullptr;
	}
}

void ObjectManager::Add(GameObject* _object, int _depth)
{
	_object->setDepth(_depth);
	ID++;
	m_objects.insert( std::pair<int, GameObject>(ID, *_object));
}

void ObjectManager::destroy(int _ID)
{
	std::map<int, GameObject>::iterator pos = m_objects.find(_ID);
	m_objects.erase(pos);
}

int ObjectManager::getObjects()
{
	return m_objects.size();
}

int ObjectManager::atPosition(sf::Vector2f _pos)
{
	for(auto object: m_objects)
	{
		sf::Vector2f pos = object.second.getPosition();
		sf::Vector2f size = object.second.getSprite()->getSize();

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

void ObjectManager::Draw(sf::RenderWindow* _window)
{
	for(int z = m_min_z; z <= m_max_z; z++)
	{
		for(auto object: m_objects)
		{
			if (object.second.getDepth() == z && object.second.hasSprite())
			{
				//std::cout << object.depth << std::endl;
				_window->draw(*object.second.getSprite());
				
				/*
				sf::RectangleShape shape;
				shape.setOutlineColor(sf::Color(255,0,0,128));
				shape.setOutlineThickness(1);
				shape.setSize(sf::Vector2f(128,128));
				shape.setFillColor(sf::Color(0,0,0,0));
				shape.setPosition(object.obj.getCollider()->m_pos);

				_window->draw(shape);*/
			}
		}
	}
}

void CheckCollision(GameObject* _object, sf::Vector2f& _offset)
{

}