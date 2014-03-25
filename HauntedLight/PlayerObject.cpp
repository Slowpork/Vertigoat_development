// PlayerObject.cpp

#include "PlayerObject.h"

#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Mouse.hpp"
#include "AnimatedSprite.h"

#include "InputManager.h"
#include "Collider.h"
#include "System.h"

#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "SFML\Audio\Music.hpp"

#include "SoundManager.h"

#include <string>
#include <iostream>

PlayerObject::PlayerObject(KeyboardObject* _keyboard, MouseObject* _mouse,
	AnimatedSprite* _sprite, Collider* _collider)
	: GameObject(_sprite, _collider)
{
	m_keyboard = _keyboard;
	m_mouse = _mouse;

	m_vel = sf::Vector2f(0.f,0.f);

	m_min_friction = 0.92f;
	m_max_friction = 0.84f;
	m_friction = m_max_friction;

	m_running = false;
	m_mining = false;
	m_hold_match = true;

	m_sprite->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);

	m_health = 100.f;
	m_stamina = 100.f;
	m_matches = 3;
	m_pickaxe = 3;
	
	m_light = 1.f;
	m_candle = true;

}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::setSprites(AnimatedSprite* _idle, AnimatedSprite* _run, AnimatedSprite* _mine)
{
	m_spr_run = _run;
	m_spr_idle = m_sprite;
	m_spr_walk = m_sprite;
	m_spr_mine = _mine;

	m_spr_walk->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
	m_spr_run->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
	m_spr_idle->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
	m_spr_mine->setOrigin(m_sprite->getSize().x/3,m_sprite->getSize().y/2);
}

void PlayerObject::setVelocity(sf::Vector2f _vel)
{
	m_vel = _vel;
}

bool PlayerObject::doMine(float _deltatime)
{
	if (m_pickaxe > 0)
	{
		m_hold_match = false;
		m_mining = true;
		m_sprite = m_spr_mine;
		int prev_frame = m_sprite->getFrame();
		m_sprite->setPosition(m_pos);
		m_sprite->play(_deltatime/2);
		int cur_frame = m_sprite->getFrame();
		if (cur_frame != prev_frame && cur_frame == 2)
		{
			return true;
		}
	}
	else
		m_mining = false;

		return false;
}

bool PlayerObject::addMatch()
{
	const int CAP = 5;
	const int ADD = 3;

	m_hold_match = true;
	if (m_matches<CAP)
	{
		m_matches += 3;

		if(m_matches > CAP)
			m_matches = CAP;

		return true;
	}
	return false;
}


bool PlayerObject::addPickaxe()
{
	const int CAP = 3;

	m_hold_match = false;
	if (m_pickaxe<CAP)
	{
		m_pickaxe += CAP;
		if (m_pickaxe > CAP)
			m_pickaxe = CAP;
		return true;
	}
	return false;
}

void PlayerObject::removePickaxe()
{
	m_mining = false;
	//std::cout << "pick: " << m_pickaxe << std::endl;
	if (m_pickaxe > 0)
		m_pickaxe--;
}

bool PlayerObject::holdMatch()
{
	return m_hold_match;
}

const float PlayerObject::getHealth()
{
	return m_health;
}

void PlayerObject::setStamina(float _value)
{
	m_stamina = _value;

	if (m_stamina > 100.f)
		m_stamina = 100.f;
	if (m_stamina < 0.0f)
		m_stamina = 0.0f;
}

const float PlayerObject::getStamina()
{
	return m_stamina;
}

const int PlayerObject::getMatches()
{
	return m_matches;
}

const int PlayerObject::getPickaxe()
{
	return m_pickaxe;
	//return (int)((float)m_pickaxe*0.333f);
}

const float PlayerObject::getLight()
{
	return m_light;
}

void PlayerObject::lightCandle()
{
	m_candle = true;
	m_matches--;
}

const bool PlayerObject::hasCandle()
{
	return m_candle;
}

void PlayerObject::doFriction()
{
	m_vel *= m_friction;
}

void PlayerObject::blowout()
{
	m_candle = false;
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

void PlayerObject::updateLight(float _deltatime)
{
	if (m_candle)
	{
		if (m_light < 1.f)
			m_light += _deltatime*2;
	}
	else
	{
		if (m_light > 0.3f)
			m_light -= _deltatime*4;
	}

	if (m_light > 1.f)
		m_light = 1.f;
	if (m_light < 0.3f)
		m_light = 0.3f;
}

void PlayerObject::Update(float _deltatime)
{
	float speed = 44.f;
	speed = 32.f;

	bool moving = false;

	updateLight(_deltatime);

	// RESET MINING
	if (m_mining)
	{
		if (!m_mouse->IsDown(Left))
		{
			m_spr_mine->setFrame(0);
			m_mining = false;
		}
	}

	// MOVE
	if (!m_mining)
	{
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
	}

	// LIGHT CANDLE
	if (m_mouse->IsDownOnce(Middle) && ( m_matches > 0 || m_candle) )
	{
		
		m_candle = !m_candle;
		if (m_candle)
		m_matches--;
	}

	// MATCHES DEBUG
	if (m_keyboard->IsDownOnce(sf::Keyboard::Add) )
	{
		m_pickaxe++;
		m_matches++;
	}
	else if (m_keyboard->IsDownOnce(sf::Keyboard::Subtract) )
	{
		m_matches--;
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
				m_stamina -= _deltatime*25.f;
			}
		}
	}
	else
	{
		m_running = false;
		m_stamina = 0.f;
		m_friction = m_max_friction;
		m_candle = false;
	}

	if (!moving || !m_keyboard->IsDown(sf::Keyboard::LShift))
	{
		m_running = false;
		m_friction = m_max_friction;
		if (m_stamina < 100.f)
			m_stamina += _deltatime*(10.f + (5.f*!moving));
		else
		m_stamina = 100.f;
	}

	if (abs(m_vel.x) > 0.2 || (m_vel.y) > 0.2 )
		moving = true;

	// ANIMATE
	if (!m_mining)
	{
		if (moving)
		{
			if ( m_running)
			{
				setState("run");
				m_sprite->play(_deltatime);
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
	}

	// UPDATE
	doFriction();

	turnToPoint(m_mouse->getPos());

	m_pos += m_vel;

	/*if ( m_pos.y < 128*4)
		m_pos.y = 128*10;*/

	setPosition(m_pos);

	if ( hasCollider())
	{
		m_collider->m_pos.x -= m_collider->m_ext.x/2;
		m_collider->m_pos.y -= m_collider->m_ext.y/2;
	}
}