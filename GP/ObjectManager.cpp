// ObjectManager.cpp

#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_min_z = 0;
	m_max_z = 0;
}

void ObjectManager::Cleanup()
{
	for(auto object: m_objects)
	{
		object.obj = nullptr;
		//delete object.obj;
	}
}

void ObjectManager::Add(GameObject& _object, int _depth)
{
	Objects object;

	object.obj = _object;
	object.depth = _depth;

	m_objects.push_back(object);
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
			if (object.depth == z && object.obj.hasSprite())
			{
				//std::cout << object.depth << std::endl;
				_window->draw(*object.obj.getSprite());
				
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