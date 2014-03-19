// Button.cpp

#include "Button.h"
#include <SFML\Graphics\RenderWindow.hpp>

#include "AnimatedSprite.h"
#include "InputManager.h"

#include <iostream>

Button::Button(AnimatedSprite* _sprite, int _width, int _height, float _x, float _y, bool _onpress)
{
	m_width = _width;
	m_height = _height;
	m_position.x = _x;
	m_position.y = _y;

	m_sprite = _sprite;
	m_sprite->setPosition(m_position.x, m_position.y);

	m_onpress = _onpress;

	m_opacity = 0;
}

Button::~Button()
{

}

bool Button::Update(float _deltatime, MouseObject* _mouse)
{
	m_mousePos.x = _mouse->GetX();
	m_mousePos.y = _mouse->GetY();

	if(m_mousePos.x > getPosition().x && m_mousePos.x < getPosition().x + m_width &&
	   m_mousePos.y > getPosition().y && m_mousePos.y < getPosition().y + m_height)
	{
		if (m_onpress)
		{
			if(_mouse->IsDown(Left))
			{
				m_opacity = 128;
				std::cout << "pressed";
				return true;
			}
			else{
				m_opacity += 800 * _deltatime;
			}
		}
		else
		{
			if(_mouse->IsDownOnce(Left))
			{
				m_opacity = 128;
				std::cout << "pressed";
				return true;
			}
			else{
				m_opacity += 800 * _deltatime;
			}
		}
		
	}
	else{
		m_opacity -= 400 * _deltatime;
	}

	if (m_opacity < 0.f)
		m_opacity = 0.f;
	if (m_opacity > 255.f)
		m_opacity = 255.f;
	
	return false;
}

void Button::Draw(sf::RenderWindow* _window)
{
	m_sprite->setFrame(0);
	m_sprite->setOpacity(255);
	_window->draw(*m_sprite);
	
	m_sprite->setFrame(1);
	m_sprite->setOpacity(m_opacity);
	_window->draw(*m_sprite);
}

void Button::Draw(sf::RenderWindow* _window, int _num)
{
	_window->draw(*m_sprite);
}

void Button::setSprite(AnimatedSprite* _sprite)
{
	m_sprite = _sprite;
	m_sprite->setPosition(m_position.x, m_position.y);
}

sf::Vector2i Button::getSize(){return sf::Vector2i(m_width, m_height);}
	
sf::Vector2f Button::getPosition(){return m_position;}
	
AnimatedSprite* Button::getSprite(){return m_sprite;}