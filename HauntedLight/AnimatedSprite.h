//AnimatedSprite.h

#pragma once
#include <SFML\Graphics\Sprite.hpp>

class AnimatedSprite : public sf::Sprite
{
public:

	AnimatedSprite(int _frames, int _w, int _h, int _x = 0, int _y = 0);

	void setFrame(int _frame);
	void play(float _deltatime);

	void setSpeed(float _speed);
	void setStart(int _start);
	void restart();
	
private:

private:

	int m_height;
	int m_width;
	int m_frames;

	int m_start;

	float m_speed;
	float m_global_speed;

	int m_current;
	float m_time;

	// REGULAR
	int m_x;
	int m_y;
};