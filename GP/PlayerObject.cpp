// PlayerObject

#include "stdafx.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse,
	sf::Sprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_keyboard = _keyboard;
	m_mouse = _mouse;

	m_vel = sf::Vector2f(0.f,0.f);
	m_max_vel = sf::Vector2f(256.f,256.f);

	m_friction = 0.98f;
}

void PlayerObject::turnToCursor()
{
	const sf::Vector2f point = sf::Vector2f(m_mouse->GetX(), m_mouse->GetY());
	float angle = atan2(point.y - m_pos.y,
						point.x - m_pos.x);
	m_sprite->setRotation(angle * (180/Math::PI));
}

void PlayerObject::Update(float _deltatime)
{
	const float speed = 32.f;

	if (m_keyboard->IsDown(sf::Keyboard::LShift))
	{
		m_friction = 0.95f;
	}
	else
	{
		m_friction = 0.9f;
	}

	if (m_keyboard->IsDown(sf::Keyboard::A))
	{
		m_vel.x -= speed * _deltatime;
	}
	else if (m_keyboard->IsDown(sf::Keyboard::D))
	{
		m_vel.x += speed * _deltatime;
	}
	if (m_keyboard->IsDown(sf::Keyboard::W))
	{
		m_vel.y -= speed * _deltatime;
	}
	else if (m_keyboard->IsDown(sf::Keyboard::S))
	{
		m_vel.y += speed * _deltatime;
	}

	m_vel.x *= m_friction;
	m_vel.y *= m_friction;

	/*
	if ( m_vel.x > m_max_vel.x || m_vel.x < m_max_vel.x*-1)
	{
		if (m_vel.x < 0)
			m_vel.x = m_max_vel.x*-1;
		else
			m_vel.x = m_max_vel.y;
	}

	if ( m_vel.y > m_max_vel.y || m_vel.y < m_max_vel.y*-1)
	{
		if (m_vel.y < 0)
			m_vel.y = m_max_vel.y*-1;
		else
			m_vel.y = m_max_vel.y;
	}*/

	//std::cout << "Vel X: " << m_vel.x << " Y: " << m_vel.y << std::endl;

	m_pos += m_vel;

	/*if ( hasCollider())
		m_collider->m_pos = m_pos;*/
}