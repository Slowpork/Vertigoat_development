// ObjectManager.cpp

#include "stdafx.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_max_z = 0;
}

void ObjectManager::Cleanup()
{
	for(auto object: m_objects)
	{
		object = nullptr;
		delete object;
	}
}

void ObjectManager::Add(GameObject* _object, int _depth)
{
	Objects object;

	object.obj = _object;
	object.depth = _depth;

	m_objects.push_back(&object);
}

void ObjectManager::Draw(sf::RenderWindow* _window)
{
	for(int z = 0; z < m_max_z; z++)
	{
		for(auto object: m_objects)
		{
			if (object->depth == z && object->obj->hasSprite())
			_window->draw(*object->obj->getSprite());
		}
	}
}

void CheckCollision(GameObject* _object, sf::Vector2f& _offset)
{

}