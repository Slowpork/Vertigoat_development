// Waller.cpp

#include "Waller.h"
#include "AnimatedSprite.h"
#include <SFML\Graphics\RenderWindow.hpp>

Waller::Waller(AnimatedSprite* _sprite, Collider* _col)
{
	m_sprite = _sprite;
	m_collider = _col;

	m_sprite->setOrigin((m_sprite->getSize().x/2)*m_sprite->getScale().x, m_sprite->getSize().y*m_sprite->getScale().y);
	m_pos = m_sprite->getPosition();
}

void Waller::Update(float _deltatime, sf::Vector2f _playerpos)
{
	if(getDistance(m_pos, _playerpos) < 120)
	{
		m_sprite->play(_deltatime);
	}
}

void Waller::Draw(sf::RenderWindow* _window)
{
	_window->draw(*m_sprite);
}