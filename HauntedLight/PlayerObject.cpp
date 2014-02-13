// PlayerObject.cpp

#include "PlayerObject.h"
#include "Math.h"

#include "SFML\Window\Keyboard.hpp"
#include "SFML\Graphics\Sprite.hpp"

#include "InputManager.h"
#include "Collider.h"

PlayerObject::PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse,
	sf::Sprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_keyboard = _keyboard;
	m_mouse = _mouse;

	m_vel = sf::Vector2f(0.f,0.f);
	m_max_vel = sf::Vector2f(256.f,256.f);

	m_friction = 0.98f;

	m_sprite->setOrigin(m_sprite->getLocalBounds().width/3,m_sprite->getLocalBounds().height/2);

	m_health = 100.f;
	m_stamina = 100.f;
}

void PlayerObject::turnToCursor()
{
	const sf::Vector2f point = m_mouse->getPos();//sf::Vector2f(m_mouse->GetX(), m_mouse->GetY());
	float angle = atan2(point.y - m_pos.y,
						point.x - m_pos.x);
	m_sprite->setRotation(angle * (180/Math::PI));
}

void PlayerObject::setVelocity(sf::Vector2f _vel)
{
	m_vel = _vel;
}

float PlayerObject::getHealth()
{
	return m_health;
}

float PlayerObject::getStamina()
{
	return m_stamina;
}

void PlayerObject::doFriction()
{
	m_vel *= m_friction;
}

void PlayerObject::Update(float _deltatime)
{
	const float speed = 32.f;

	if ( m_keyboard->IsDownOnce(sf::Keyboard::Up))
	{
		m_health += 10;
	}
	else if ( m_keyboard->IsDownOnce(sf::Keyboard::Down))
	{
		m_health -= 10;
	}

	bool moving = false;

	if (m_keyboard->IsDown(sf::Keyboard::A))
	{
		moving = true;
		m_vel.x -= speed * _deltatime;
	}
	else if (m_keyboard->IsDown(sf::Keyboard::D))
	{
		moving = true;
		m_vel.x += speed * _deltatime;
	}
	if (m_keyboard->IsDown(sf::Keyboard::W))
	{
		moving = true;
		m_vel.y -= speed * _deltatime;
	}
	else if (m_keyboard->IsDown(sf::Keyboard::S))
	{
		moving = true;
		m_vel.y += speed * _deltatime;
	}

	if (m_stamina > 0.f)
	{
		if (m_keyboard->IsDown(sf::Keyboard::LShift))
		{
			m_friction = 0.95f;
			if ( moving)
				m_stamina -= _deltatime*25.f;
		}
	}
	else
		m_stamina = 0.f;

	if (!moving || !m_keyboard->IsDown(sf::Keyboard::LShift))
	{
		m_friction = 0.9f;
		if (m_stamina < 100.f)
			m_stamina += _deltatime*(5.f + (5.f*!moving));
		else
		m_stamina = 100.f;
	}

	doFriction();

	turnToCursor();

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

	/*if ( hasSprite())
		m_sprite->setPosition(m_pos);*/

	setPosition(m_pos);

	if ( hasCollider())
	{
		m_collider->m_pos.x -= m_collider->m_ext.x/2;
		m_collider->m_pos.y -= m_collider->m_ext.y/2;
	}
}