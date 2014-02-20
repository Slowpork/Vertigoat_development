// PlayerObject.cpp

#include "PlayerObject.h"

#include "SFML\Window\Keyboard.hpp"
#include "AnimatedSprite.h"

#include "InputManager.h"
#include "Collider.h"

#include <string>

PlayerObject::PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse,
	AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_keyboard = _keyboard;
	m_mouse = _mouse;

	m_vel = sf::Vector2f(0.f,0.f);

	m_min_friction = 0.92f;
	m_max_friction = 0.88f;
	m_friction = m_max_friction;

	m_running = false;

	m_sprite->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);

	m_health = 100.f;
	m_stamina = 100.f;
}

void PlayerObject::setSprites(AnimatedSprite* _idle, AnimatedSprite* _run)
{
	m_spr_run = _run;
	m_spr_idle = m_sprite;
	m_spr_walk = m_sprite;

	m_spr_walk->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
	m_spr_run->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
	m_spr_idle->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
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

void PlayerObject::setState(std::string _state)
{
	if (_state == "idle")
	{
		m_sprite = m_spr_idle;
	}
	else if (_state == "walk" )
	{
		m_sprite = m_spr_walk;
	}
	else if (_state == "run")
	{
		m_sprite = m_spr_run;
	}
}

void PlayerObject::Update(float _deltatime)
{
	const float speed = 44.f;

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
			m_friction = m_min_friction;
			if ( moving)
			{
				m_running = true;
				//m_stamina -= _deltatime*25.f;
			}
		}
	}
	else
	{
		m_running = false;
		m_stamina = 0.f;
	}

	if (!moving || !m_keyboard->IsDown(sf::Keyboard::LShift))
	{
		m_running = false;
		m_friction = m_max_friction;
		if (m_stamina < 100.f)
			m_stamina += _deltatime*(5.f + (5.f*!moving));
		else
		m_stamina = 100.f;
	}

	// ANIMATE
	if (moving)
	{
		if ( m_running)
		{
			setState("walk");
			m_sprite->play(_deltatime*1.3);
		}
		else
		{
			setState("walk");
			m_sprite->play(_deltatime);
		}
	}
	else
	{
		setState("idle");
		//m_sprite->play(_deltatime);
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