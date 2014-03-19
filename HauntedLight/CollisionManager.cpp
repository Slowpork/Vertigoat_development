// CollisionManager.cpp

#include "ObjectManager.h"
#include "PickupManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include <math.h>

CollisionManager::CollisionManager(ObjectManager* _object_manager, PickupManager* _pickup_manager)
{
	m_object_manager = _object_manager;
	m_pickup_manager = _pickup_manager;
};

bool CollisionManager::RectvsRect(Collider* _object, Collider* _other, sf::Vector2f& _offset)
{
	float A = _object->m_ext.x * 0.5f;
	float B = _other->m_ext.x * 0.5f;
	float C = (_object->m_pos.x + A) - (_other->m_pos.x + B);

	if ( fabs(C) <= A + B)
	{
		float Q = _object->m_ext.y * 0.5f;
		float P = _other->m_ext.y * 0.5f;
		float Z = (_object->m_pos.y + Q) - (_other->m_pos.y + P);

		if ( fabs(Z) <= Q + P)
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

int CollisionManager::checkCollision(Collider* _object, sf::Vector2f& _offset, Manager _type,int& _ID)
{
	int count = 0, VALUE = 0;
	//std::cout << m_object_manager->m_objects.size() << std::endl;

	std::map<int,GameObject*>::iterator start;
	std::map<int,GameObject*>::iterator end;

	switch(_type)
	{
	case WALLS:
		start = m_object_manager->m_objects.begin();
		end = m_object_manager->m_objects.end();
	break;
	case PICKUPS:
		start = m_pickup_manager->m_objects.begin();
		end = m_pickup_manager->m_objects.end();
	break;
	}
	
	for(std::map<int,GameObject*>::iterator object = start; object != end; object++)
	{
		//std::cout << object.obj.getCollider() << std::endl;
		//std::cout << object.obj.m_collider->m_type << std::endl;
		if (object->second->getCollider())
		{
			sf::Vector2f _off;
			if (_object->m_type == Rect && object->second->getCollider()->m_type == Rect)
			{
				if ( RectvsRect(_object, object->second->getCollider(), _off))
				{
					_offset += _off;
					count++;
					VALUE = object->second->getDepth();
					_ID = object->first;
				}
			}
			//else if (_object->m_type == Circle)
		}
		
	}

	if (count > 0)
	{
		_offset /= (float)count;

		_offset.x = floorf(_offset.x);
		_offset.y = floorf(_offset.y);

		return VALUE;
	}

	return false;
}