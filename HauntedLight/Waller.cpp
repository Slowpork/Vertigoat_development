// Waller.cpp

#include "Waller.h"
#include "AnimatedSprite.h"
#include <SFML\Graphics\RenderWindow.hpp>

#include <iostream>

Waller::Waller(AnimatedSprite* _sprite, Collider* _col)
	: EnemyObject(_sprite, _col)
{
	m_sprite = _sprite;
	m_collider = _col;

	//m_sprite->setOrigin((m_sprite->getSize().x/2)*m_sprite->getScale().x, (m_sprite->getSize().y/2)*m_sprite->getScale().y);
	m_pos = m_sprite->getPosition();
}

void Waller::Update(float _deltatime, sf::Vector2f _playerpos)
{
	if(hasSprite()){

	m_sprite->setOrigin((m_sprite->getSize().x/2)*m_sprite->getScale().x,
						(m_sprite->getSize().y/2)*m_sprite->getScale().y);

	if(getDistance(m_pos, _playerpos) < 100)
	{
		if(alt_sprite)
		{
			AnimatedSprite* spr_temp;
			spr_temp = m_sprite;

			m_sprite = m_sprite_alt;
			addSprite(spr_temp);

			alt_sprite = !alt_sprite;
		}

		m_sprite->play(_deltatime);
	}else{
		if(!alt_sprite)
		{
			AnimatedSprite* spr_temp;
			spr_temp = m_sprite;

			m_sprite = m_sprite_alt;
			addSprite(spr_temp);

			alt_sprite = !alt_sprite;
		}
	}

	m_sprite->setOpacity(255);
	}else{
		std::cout << "No sprite" << std::endl;
	}
}

void Waller::Draw(sf::RenderWindow* _window)
{
	_window->draw(*m_sprite);
}