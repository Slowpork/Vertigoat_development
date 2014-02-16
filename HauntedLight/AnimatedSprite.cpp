//AnimatedSprite.cpp

#include "AnimatedSprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(int _frames, int _w, int _h, int _x, int _y)
{
	m_frames = _frames;
	m_time = 0.0f;

	m_width = _w;
	m_height = _h;

	// REGULAR
	m_x = _x;
	m_y = _y;

	m_global_speed = 1.f;
	m_speed = 0.1f;
	m_current = 0;
	m_start = 0;
}

void AnimatedSprite::restart()
{
	m_current = m_start;
	setFrame(m_current);
}

void AnimatedSprite::setStart(int _start)
{
	m_start = _start;
}

void AnimatedSprite::setSpeed(float _speed)
{
	m_global_speed = _speed;
}

sf::Vector2f AnimatedSprite::getSize()
{
	return sf::Vector2f(m_width,m_height);
}

void AnimatedSprite::setFrame(int _frame)
{
	//std::cout << "  X: " << _frame * m_width << " Y: " << m_y << " W: " << m_width << " H: " << m_height << std::endl;
	setTextureRect(sf::IntRect(sf::Vector2i((_frame * m_width) + m_x, m_y),sf::Vector2i(m_width, m_height)));
}

void AnimatedSprite::play(float _deltatime)
{
	m_time += _deltatime;
	if( m_time >= m_speed/m_global_speed) 
	{
		m_time = 0.0f;
		m_current = ++m_current % m_frames;

		setFrame(m_current);
	};
}