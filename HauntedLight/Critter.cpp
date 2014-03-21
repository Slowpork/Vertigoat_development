// Critter.cpp

#include "Critter.h"
#include "AnimatedSprite.h"
#include <SFML\Graphics\RenderWindow.hpp>

Critter::Critter(AnimatedSprite* _sprite, Collider* _collider)
{
	m_sprite = _sprite;
	m_collider = _collider;

	m_chase = false;
	m_dir = sf::Vector2f(0,0);

	m_sprite->setOrigin((m_sprite->getSize().x/2)*m_sprite->getScale().x, (m_sprite->getSize().y)*m_sprite->getScale().y);
	m_homePos = m_sprite->getPosition();
}

void Critter::Update(float _deltatime, sf::Vector2f _playerpos)
{
	m_pos = m_sprite->getPosition();
	const float speed = 32.f;

	if(getDistance(m_pos, _playerpos) < 150.f)
	{
		m_chase = true;
	}

	if(m_chase)
	{
		m_timer += _deltatime;

		turnToPoint(_playerpos);
		m_dir = getDirection(m_pos, _playerpos);

		m_vel.x += speed * m_dir.x * _deltatime;
		m_vel.y += speed * m_dir.y * _deltatime;
	}

	if(m_timer > 5.f)
	{
		m_timer = 0;
		m_chase = false;

		turnToPoint(m_homePos);
		m_dir = getDirection(m_pos, m_homePos);

		m_vel.x += speed*m_dir.x*_deltatime;
		m_vel.y += speed*m_dir.y*_deltatime;
	}

	doFriction();
	m_pos += m_vel;
	setPosition(m_pos);
}void Critter::Draw(sf::RenderWindow* _window)
{
	_window->draw(*m_sprite);
}