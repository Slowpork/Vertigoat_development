// CollisionManager.cpp

#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager(ObjectManager* _object_manager)
{
	m_object_manager = _object_manager;
};

bool CollisionManager::RectvsRect(Collider* _object, Collider* _other, sf::Vector2f& _offset)
{
	
	float A = _object->m_ext.x * 0.5f;
	float B = _other->m_ext.x * 0.5f;
	float C = (_object->m_pos.x + A) - (_other->m_pos.x + B);

	if ( fabs(C) < A + B)
	{
		float Q = _object->m_ext.y * 0.5f;
		float P = _other->m_ext.y * 0.5f;
		float Z = (_object->m_pos.y + Q) - (_other->m_pos.y + P);

		if ( fabs(Z) < Q + P)
		{
			float dx = fabs(C) - (A + B);
			float dy = fabs(Z) - (Q + P);

			if ( dx >= dy)
			{
				if ( _object->m_pos.x > _other->m_pos.x)
				{
					dx = -dx;
				}
				_offset.x = dx;
				_object->m_pos.x += dx;
			}
			else
			{
				if ( _object->m_pos.y > _other->m_pos.y)
				{
					dy = -dy;
				}
				_offset.y = dy;
				_object->m_pos.y += dy;
			}	

			return true;
		}
	}

	return false;
	

	/*
	if ( _object->m_pos.x > _other->m_pos.x && _object->m_pos.x < _other->m_pos.x + _other->m_ext.x )
	{
		if ( _object->m_pos.y > _other->m_pos.y && _object->m_pos.y < _other->m_pos.y + _other->m_ext.y)
		{
			return true;
		}
	}
	
	return false;*/
}

bool CollisionManager::checkCollision(Collider* _object, sf::Vector2f& _offset)
{
	std::cout << m_object_manager->m_objects.size() << std::endl;
	for(auto object: m_object_manager->m_objects)
	{
		std::cout << object.obj.getCollider() << std::endl;
		//std::cout << object.obj.m_collider->m_type << std::endl;
		if (_object->m_type == Rect && object.obj.m_collider->m_type == Rect)
			return RectvsRect(_object, object.obj.m_collider, _offset);
		//else if (_object->m_type == Circle)
	}

	return false;
}