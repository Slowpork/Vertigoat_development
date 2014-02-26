// PauseState.cpp

#include "PauseState.h"

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

PauseState::PauseState(System* _system)
{
	m_name = "PauseState";
	m_next = "GameState";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool PauseState::Enter(){
	//std::cout << m_name << std::endl;
	m_paused = false;
	return true;
}
void PauseState::Exit(){
	//std::cout << "  " << m_name << "->";
}

void PauseState::Pause()
{
	m_paused = true;
}

void PauseState::Resume()
{
	m_paused = false;
}

bool PauseState::Update(float deltatime){
	//std::cout << "PauseState::Update" << std::endl;

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::P))
	{
		m_next = "";
		return false;
	} else if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
		m_next = "MenuState";
		return false;
	}

	return true;
}
void PauseState::Draw(){
	//std::cout << "PauseState::Draw" << std::endl;

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f( m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));

	m_system->m_window->draw(rect_fade);

	object_manager->Draw(m_system->m_window);
}
std::string PauseState::Next(){
	//std::cout << "Goto GameState\n--" << std::endl;
	return m_next;
}
bool PauseState::IsType(const std::string &type){
	return type.compare(m_name) == 0;
}

bool PauseState::isPaused()
{
	return m_paused;
}

bool PauseState::isBase()
{
	return m_base;
}