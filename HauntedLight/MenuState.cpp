//MenuState.cpp

#include "MenuState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\View.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"

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

MenuState::MenuState(System* _system)
{
	m_name = "MenuState";
	m_next = "LoadingState";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
}

bool MenuState::Enter()
{
	//std::cout << m_name << std::endl;
	m_paused = false;
	m_base = true;

	object_manager = new ObjectManager();

	spr_menu = m_system->m_sprite_manager->getSprite("spr_main_menu.png",0,0,1288,720);

	return true;
}

void MenuState::Exit()
{
	//std::cout << "  " << m_name << "->";

	delete spr_menu;
	spr_menu = nullptr;

	m_paused = false;
}

void MenuState::Pause()
{
	m_paused = true;
}

void MenuState::Resume()
{
	m_paused = false;
}

bool MenuState::Update(float _deltatime){
	//std::cout << "MenuState::Update" << std::endl;

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
		m_next = "";
		return false;
	}
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Space))
	{
		m_next = "GameState";
		return false;
	}
	else
		return true;
}

void MenuState::Draw(){
	//std::cout << "MenuState::Draw" << std::endl;

	m_system->m_window->setView(m_system->m_window->getDefaultView());
	m_system->m_window->draw(*spr_menu);
}

std::string MenuState::Next(){
	//std::cout << "MenuState::next" << std::endl;
	return m_next;
}

bool MenuState::IsType(const std::string &type) {

	//std::cout << "MenuState::IsType" << std::endl;

	return type.compare(m_name) == 0;
}

bool MenuState::isPaused()
{
	return m_paused;
}

bool MenuState::isBase()
{
	return m_base;
}