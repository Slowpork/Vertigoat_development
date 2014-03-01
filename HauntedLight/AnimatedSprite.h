//AnimatedSprite.h

#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Vector2.hpp>

class AnimatedSprite : public sf::Sprite
{
public:

	AnimatedSprite(int _frames, int _w, int _h, int _x = 0, int _y = 0);

	void setFrame(int _frame);
	int getFrame();
	void play(float _deltatime);

	sf::Vector2f getSize();
	void turnToPoint(sf::Vector2f _point, float _speed = 0.f);

	void setOpacity(int _alpha);
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