// Crawler.cpp

#include "Crawler.h"

#include "SFML\Graphics\RenderWindow.hpp"

#include "AnimatedSprite.h"

#include <iostream>

Crawler::Crawler(AnimatedSprite* _sprite, Collider* _col)
	: EnemyObject(_sprite, _col)
{

}

void Crawler::Draw(sf::RenderWindow* _window)
{
	m_sprite->setPosition(sf::Vector2f(getPosition().x + 64.f, getPosition().y + 64.f));
	_window->draw(*m_sprite);
}

void Crawler::setSprite(AnimatedSprite* _sprite)
{
	m_spr_idle = m_sprite;
	m_spr_turn = _sprite;
}

void Crawler::setPath(std::vector<sf::Vector2f>* _path)
{
	m_current_node = 0;
	if (m_path != nullptr)
	{
		delete m_path;
		m_path = nullptr;
	}
	m_path = _path;
}

bool Crawler::turn(int _dir)
{

	return false;
}

void Crawler::Update(float _deltatime, sf::Vector2f _playerpos)
{
	float speed = 44.f;

	m_sprite->play(_deltatime);

	if (m_path != nullptr) // PATHFINDING
	{
		sf::Vector2f dest(m_path->at(m_current_node).x + 64.f,m_path->at(m_current_node).y + 64.f);
		
		if (m_pos.x < dest.x)
			m_pos.x += speed *_deltatime * 10;
		else if (m_pos.x > dest.x)
			m_pos.x -= speed *_deltatime * 10;

		if (m_pos.y < dest.y)
			m_pos.y += speed *_deltatime * 10;
		else if (m_pos.y > dest.y)
			m_pos.y -= speed *_deltatime * 10;


		int goal_count = 0;
		if ( abs(m_pos.x - dest.x) < 8 ) // X AXIS DONE
		{
			m_pos.x = dest.x;
			goal_count++;
		}

		if ( abs(m_pos.y - dest.y) < 8 ) // Y AXIS DONE
		{
			m_pos.y = dest.y;
			goal_count++;
		}

		if (goal_count == 2) // AT POSITION - set next || clear
		{
			m_pos = dest;
			m_current_node++;
			std::cout << "  Node: " << m_current_node << "  X: " << dest.x << " Y: " << dest.y << std::endl;
			if (m_current_node == m_path->size())
			{
				m_current_node = 0;
				m_path->clear();
				delete m_path;
				m_path = nullptr;
			}
		}
	}
}