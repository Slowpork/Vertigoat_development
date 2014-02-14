// PlayerObject.cpp

#include "PlayerObject.h"

#include "SFML\Window\Keyboard.hpp"
#include "AnimatedSprite.h"

#include "InputManager.h"
#include "Collider.h"

PlayerObject::PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse,
	AnimatedSprite* _sprite, Collider* _collider)
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

	bool moving = false;

	// MOVE
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

	// RUN
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

	if (moving)
	{
		m_sprite->play(_deltatime);
	}

	// UPDATE
	doFriction();

	turnToPoint(m_mouse->getPos());

	m_pos += m_vel;

	setPosition(m_pos);

	if ( hasCollider())
	{
		m_collider->m_pos.x -= m_collider->m_ext.x/2;
		m_collider->m_pos.y -= m_collider->m_ext.y/2;
	}
}