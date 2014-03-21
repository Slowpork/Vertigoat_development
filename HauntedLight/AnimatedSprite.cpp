//AnimatedSprite.cpp

#include "AnimatedSprite.h"

#include <iostream>
#include <math.h>
#include "Math.h"

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

// 0-255
void AnimatedSprite::setOpacity(int _alpha)
{
	sf::Color current = getColor();
	setColor(sf::Color(current.r,current.g,current.b,_alpha));
}

sf::Vector2f AnimatedSprite::getSize()
{
	return sf::Vector2f(m_width,m_height);
}

void AnimatedSprite::setFrame(int _frame)
{
	m_current = _frame;
	setTextureRect(sf::IntRect(sf::Vector2i((_frame * m_width) + m_x, m_y),sf::Vector2i(m_width, m_height)));
}

int AnimatedSprite::getFrame()
{
	return m_current;
}

void AnimatedSprite::play(float _deltatime)
{
	m_time += _deltatime;
	if( m_time >= m_speed/m_global_speed) 
	{
		m_time = 0.0f;
		m_current = ++m_current % m_frames;

		setFrame(m_current);
	}
}

void AnimatedSprite::turnToPoint(sf::Vector2f _point, float _speed)
{
	float angle = atan2(_point.y - getPosition().y,
							_point.x - getPosition().x);
	float desired = angle * (180/Math::PI);

	if (_speed == 0.f ) // DIRECT TURN
	{
		setRotation(desired);
	}
	else // INCREMENTAL TURN
	{
		float wdir, tempdir, turnspeed;
		wdir = desired;
		turnspeed = _speed;
		if (abs(wdir-getRotation()) > 180) {
			if (wdir > 180) {
				tempdir = wdir - 360;
				if (abs(tempdir-getRotation()) > turnspeed) {
					setRotation(getRotation() - turnspeed);
				} else {
					setRotation(wdir);
				}
			} else {
				tempdir = wdir + 360;
				if (abs(tempdir-getRotation()) > turnspeed) {
					setRotation(getRotation() + turnspeed);
				} else {
					setRotation(wdir);
				}
			}
		} else {
			if (abs(wdir - getRotation()) > turnspeed) {
				if (wdir > getRotation()) {
					setRotation(getRotation() + turnspeed);
				} else {
					setRotation(getRotation() - turnspeed);
				}
			} else {
				setRotation(wdir);
			}
		}
	}

	//std::cout << "X: " << getPosition().x << " Y:"  << getPosition().y << std::endl;
}