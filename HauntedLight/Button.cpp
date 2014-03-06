//Button.cpp

#include "Button.h"
#include <SFML\Graphics\RenderWindow.hpp>

Button::Button(AnimatedSprite* _sprite, int _width, int _height, float _x, float _y)
{
	m_width = _width;
	m_height = _height;
	m_position.x = _x;
	m_position.y = _y;

	m_sprite = _sprite;
	m_sprite->setPosition(m_position.x, m_position.y);

	m_opacity = 0;
}

Button::~Button()
{
	delete m_sprite; m_sprite = nullptr;
}

void Button::Update(float _deltatime, MouseObject* _mouse)
{
	m_active = false;
	m_mousePos.x = _mouse->GetX();
	m_mousePos.y = _mouse->GetY();

	if(m_mousePos.x > getPosition().x && m_mousePos.x < getPosition().x + m_width &&
	   m_mousePos.y > getPosition().y && m_mousePos.y < getPosition().y + m_height)
	{
		if(_mouse->IsDown(Left))
		{
			m_active = true;
			m_opacity = 128;
		}else{
			if(m_opacity < 255)
			{
				m_opacity += 150 * _deltatime;
			}else if(m_opacity >= 255){
				m_opacity = 255;
			}
		}
	}else{
		if(m_opacity > 0)
		{
			m_opacity -= 150 * _deltatime;
		}
	}
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

sf::Vector2i Button::getSize(){return sf::Vector2i(m_width, m_height);}
	
sf::Vector2f Button::getPosition(){return m_position;}
	
AnimatedSprite* Button::getSprite(){return m_sprite;}

bool Button::isClicked(){return m_active;}