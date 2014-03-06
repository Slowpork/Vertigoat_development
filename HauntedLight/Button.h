//Button.h

#pragma once

#include "AnimatedSprite.h"
#include "InputManager.h"

#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RenderWindow;
}

class Button
{
public:
	Button(AnimatedSprite* _sprite, int _width, int _height, float _x, float _y);
	~Button();

	void Update(float _deltatime, MouseObject* _mouse);
	void Draw(sf::RenderWindow* _window);
	
	sf::Vector2i getSize();
	sf::Vector2f getPosition();
	AnimatedSprite* getSprite();

	bool isClicked();

private:

private:
	int m_width;
	int m_height;
	int m_opacity;
	bool m_active;
	sf::Vector2f m_position;
	AnimatedSprite* m_sprite;
	sf::Vector2i m_mousePos;
};