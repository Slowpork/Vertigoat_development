// Crawler.cpp

#include "Crawler.h"

#include "SFML\Graphics\RenderWindow.hpp"

#include "AnimatedSprite.h"
#include "Collider.h"

#include <iostream>

Crawler::Crawler(AnimatedSprite* _sprite, Collider* _col)
	: EnemyObject(_sprite, _col)
{
	m_dir = 0;
	m_turning = false;
}

void Crawler::Draw(sf::RenderWindow* _window)
{
	m_sprite->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
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

void Crawler::turn()
{
	int frame = m_sprite->getFrame();

	if (frame == m_sprite->getFrames() - 1 )
	{
		
		m_turning = false;
		m_sprite = m_spr_idle;
	}

	if (frame == 11 || frame == m_sprite->getFrames() - 1 ) // ROTATE
	{
		switch (m_dir)
		{
		case 0:
			m_sprite->setRotation(270);
		break;
		case 1:
			m_sprite->setRotation(180);
		break;
		case 2:
			m_sprite->setRotation(90);
		break;
		case 3:
			m_sprite->setRotation(0);
		break;
		}
	}
}

bool Crawler::needPath()
{
	if (m_path == nullptr)
		return true;
	else 
		return false;
}

int Crawler::getDir()
{
	if (m_pos.y < m_path->at(m_current_node).y)
	return 0;
	if (m_pos.x > m_path->at(m_current_node).x)
	return 1;
	if (m_pos.y > m_path->at(m_current_node).y)
	return 2;
	if (m_pos.x < m_path->at(m_current_node).x)
	return 3;
}

void Crawler::Update(float _deltatime, sf::Vector2f _playerpos)
{
	float speed = 44.f;

	m_sprite->play(_deltatime);

	if (m_turning)
	turn();
	else if (m_path != nullptr) // PATHFINDING
	{
		sf::Vector2f dest(m_path->at(m_current_node).x + 64.f,m_path->at(m_current_node).y + 64.f);

		int prev_dir = m_dir;
		
		if (m_pos.x < dest.x)
		{
			m_dir = 1;
			m_pos.x += speed *_deltatime * 2;
		}
		else if (m_pos.x > dest.x)
		{
			m_dir = 3;
			m_pos.x -= speed *_deltatime * 2;
		}

		if (m_pos.y < dest.y)
		{
			m_dir = 0;
			m_pos.y += speed *_deltatime * 2;
		}
		else if (m_pos.y > dest.y)
		{
			m_dir = 2;
			m_pos.y -= speed *_deltatime * 2;
		}

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
			//std::cout << "dir: " << m_dir << "prev: " << prev_dir << std::endl;
			
			if (m_current_node == m_path->size())
			{
				//std::cout << "Deleted path..." << std::endl;
				m_current_node = 0;
				m_path->clear();
				delete m_path;
				m_path = nullptr;
			}

			m_dir = getDir();
			std::cout << "dir: " << m_dir;
			if (prev_dir != m_dir && m_path != nullptr)
			{
				m_sprite = m_spr_turn;
				m_sprite->setFrame(0);
				m_turning = true;
			}
		}
	}
	setPosition(m_pos);
}