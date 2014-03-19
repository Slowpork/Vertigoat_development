// Button.h

#pragma once

#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RenderWindow;
}

class MouseObject;
class AnimatedSprite;

class Button
{
public:
	Button(AnimatedSprite* _sprite, int _width, int _height, float _x, float _y, bool _onpress = false);
	~Button();

	bool Update(float _deltatime, MouseObject* _mouse);
	void Draw(sf::RenderWindow* _window);
	void Draw(sf::RenderWindow* _window, int _num);
	void setSprite(AnimatedSprite* _sprite);

	sf::Vector2i getSize();
	sf::Vector2f getPosition();
	AnimatedSprite* getSprite();

private:

private:
	int m_width;
	int m_height;
	int m_opacity;

	bool m_onpress;
	sf::Vector2f m_position;
	AnimatedSprite* m_sprite;
	sf::Vector2i m_mousePos;
};