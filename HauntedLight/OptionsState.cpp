//OptionsState.cpp

#include "OptionsState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\View.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\System\Vector2.hpp"

#include "System.h"

#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "InputManager.h"

#include "SFML\Window\Keyboard.hpp"

#include "Wall.h"
#include "PlayerObject.h"
#include "AnimatedSprite.h"

#include "Collider.h"

OptionsState::OptionsState(System* _system)
{
	m_name = "OptionsState";
	m_next = "";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	state = 0;

	m_system = _system;
}

bool OptionsState::Enter(){
	std::cout << m_name << std::endl;

	state = 0;

	object_manager = new ObjectManager();

	sf::Vector2f scale = sf::Vector2f((float)m_system->m_width/1280.f,(float)m_system->m_height/720.f);

	//ButtonTest
	spr_volume_low = m_system->m_sprite_manager->getSprite("Options/spr_volume_low.png",0,0,128,128);
	spr_volume_low->setScale(scale.x/2,scale.y/2);
	spr_volume_low->setOrigin(100.f,100);
	spr_volume_low->setPosition(m_system->m_width/2 + 6*scale.x, m_system->m_height/2 - 54.f*scale.y + 24*scale.y);


	return true;
}
void OptionsState::Exit()
{
	std::cout << "  " << m_name << "->";

	delete spr_background;
	spr_background = nullptr;

	delete object_manager;
	object_manager = nullptr;

	m_paused = false;
}

void OptionsState::Pause()
{
	m_paused = true;
}

void OptionsState::Resume()
{
	m_paused = false;
}

bool OptionsState::Update(float _deltatime){
	//std::cout << "OptionsState::Update" << std::endl;
	
/*
	switch(state)
	{
	case 0:
		if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Space))
		{
			state = 1;
		}
	case 1:
		m_next = "MenuState";
		return false;
		break;
	}
*/
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
        m_next = "";
		return false;
	}

	return true;	
}

void OptionsState::Draw(){
	//std::cout << "OptionsState::Draw" << std::endl;

	//m_system->m_window->setView(m_system->m_window->getDefaultView());

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f( m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));

	m_system->m_window->draw(rect_fade);

//	m_system->m_window->draw(*spr_background);

	m_system->m_window->draw(*spr_volume_low);

//	object_manager->Draw(m_system->m_window);
}

std::string OptionsState::Next(){
	//std::cout << "OptionsState::next" << std::endl;
	return m_next;
}

bool OptionsState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}

bool OptionsState::isPaused()
{
	return m_paused;
}

bool OptionsState::isBase()
{
	return m_base;
}