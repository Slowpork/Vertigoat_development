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

	object_manager = new ObjectManager();

	return true;
}

void MenuState::Exit()
{
	//std::cout << "  " << m_name << "->";
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

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::M))
	{
		m_next = "LoadingState";
		return false;
	}
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::P))
	{
		m_next = "";
		return false;
	}
	else
		return true;
}

void MenuState::Draw(){
	//std::cout << "MenuState::Draw" << std::endl;

	m_system->m_window->setView(m_system->m_window->getDefaultView());
	sf::RectangleShape rect(sf::Vector2f( 
		m_system->m_width, 
		m_system->m_height));
	rect.setOutlineColor(sf::Color::Red);
	rect.setPosition(0,0);
	rect.setOutlineThickness(2.f);
	rect.setFillColor(sf::Color(0,0,0,128));

	m_system->m_window->draw(rect);
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