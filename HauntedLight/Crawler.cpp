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
	snap_factor = 4.f;
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
	decideDir();
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
		//std::cout << "DIRECTION!!!!: " << m_dir << std::endl;
		switch (m_dir)
		{
		case 0:
			//std::cout << "UP" << std::endl;
			m_sprite->setRotation(-90);
			m_spr_idle->setRotation(-90);
		break;
		case 1:
			//std::cout << "RIGHT" << std::endl;
			m_sprite->setRotation(0);
			m_spr_idle->setRotation(0);
		break;
		case 3:
			//std::cout << "LEFT" << std::endl;
			m_sprite->setRotation(180);
			m_spr_idle->setRotation(180);
		break;
		case 2:
			//std::cout << "DOWN" << std::endl;
			m_sprite->setRotation(90);
			m_spr_idle->setRotation(90);
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

void Crawler::setDir()
{
	//std::cout << "  setDir()" << std::endl;
	//std::cout << "X: " <<  m_path->at(m_current_node).x << " Y: " <<  m_path->at(m_current_node).y << std::endl;
	if (m_pos.y > m_path->at(m_current_node).y + 64.f)
	{
		if (m_pos.y - m_path->at(m_current_node).y + 64.f > snap_factor )
		{
			//std::cout << "UP" << std::endl;
			m_dir = 0;
		}
	}
	if (m_pos.x > m_path->at(m_current_node).x + 64.f )
	{
		if ( m_pos.x - m_path->at(m_current_node).x + 64.f > snap_factor )
		{
			//std::cout << "LEFT" << std::endl;
			m_dir = 3;
		}
	}
	if (m_pos.y < m_path->at(m_current_node).y + 64.f )
	{
		if ( m_path->at(m_current_node).y + 64.f - m_pos.y > snap_factor )
		{
			//std::cout << "DOWN" << std::endl;
			m_dir = 2;
		}
	}
	if (m_pos.x < m_path->at(m_current_node).x + 64.f)
	{
		if (m_path->at(m_current_node).x + 64.f - m_pos.x > snap_factor )
		{
			//std::cout << "RIGHT" << std::endl;
			m_dir = 1;
		}
	}
}

void Crawler::decideDir()
{
	if (m_path != nullptr)
	{
		int prev_dir = m_dir;
		setDir();
		//std::cout << "prev: " << prev_dir << " dir: " << m_dir << std::endl;

		if (prev_dir != m_dir )
		{
			m_sprite = m_spr_turn;
			m_sprite->setFrame(0);
			m_turning = true;
		}
	}
}

void Crawler::Update(float _deltatime, sf::Vector2f _playerpos)
{
	float speed = 44.f;

	m_sprite->play(_deltatime* (1 + m_turning));

	if (m_turning)
	turn();
	else if (m_path != nullptr) // PATHFINDING
	{
		sf::Vector2f dest(m_path->at(m_current_node).x + 64.f,m_path->at(m_current_node).y + 64.f);
		
		if (m_pos.x < dest.x)
			m_pos.x += speed *_deltatime * 5;
		else if (m_pos.x > dest.x)
			m_pos.x -= speed *_deltatime * 5;

		if (m_pos.y < dest.y)
			m_pos.y += speed *_deltatime * 5;
		else if (m_pos.y > dest.y)
			m_pos.y -= speed *_deltatime * 5;

		int goal_count = 0;
		if ( abs(m_pos.x - dest.x) < snap_factor ) // X AXIS DONE
		{
			m_pos.x = dest.x;
			goal_count++;
		}

		if ( abs(m_pos.y - dest.y) < snap_factor ) // Y AXIS DONE
		{
			m_pos.y = dest.y;
			goal_count++;
		}

		if (goal_count == 2) // AT POSITION - set next || clear
		{
			m_pos = dest;
			m_current_node++;
			
			if (m_current_node == m_path->size())
			{
				//std::cout << "Deleted path..." << std::endl;
				m_current_node = 0;
				m_path->clear();
				delete m_path;
				m_path = nullptr;
			}

			decideDir();
		}
	}

	setPosition(m_pos);
}