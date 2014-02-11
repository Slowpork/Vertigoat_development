// PlayerObject

#include "stdafx.h"
#include "PlayerObject.h"

PlayerObject::PlayerObject(Keyboard* _keyboard, Mouse* _mouse)
{
	m_keyboard = _keyboard;
	m_mouse = _mouse;

	m_vel = sf::Vector2f(0.f,0.f);
	m_max_vel = sf::Vector2f(256.f,256.f);

	m_friction = 0.9f;
}

void PlayerObject::Update(float _deltatime)
{
	const float speed = 32.f;

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
	}

	std::cout << "Vel X: " << m_vel.x << " Y: " << m_vel.y << std::endl;

	m_pos += m_vel;

	/*if ( hasCollider())
		m_collider->m_pos = m_pos;*/
}