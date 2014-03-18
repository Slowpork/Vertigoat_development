//OptionsState.cpp

#include "CreditsState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML/Window/Keyboard.hpp"

#include "System.h"

#include "ObjectManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "FontManager.h"

#include "AnimatedSprite.h"
#include "Button.h"

/*

	Sound Bar Dimensions: 456x128px

*/

CreditsState::CreditsState(System* _system)
{
	m_name = "CreditsState";
	m_next = "";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
}

bool CreditsState::Enter(){
	std::cout << m_name << std::endl;

	return true;
}
void CreditsState::Exit()
{
	std::cout << "  " << m_name << "->";

	m_paused = false;
}

void CreditsState::Pause()
{
	m_paused = true;
}

void CreditsState::Resume()
{
	m_paused = false;
}

bool CreditsState::Update(float _deltatime){
	//std::cout << "CreditsState::Update" << std::endl;

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::C) )
	{
		m_next = "";
		return false;
	}

	return true;
}

void CreditsState::Draw(){
	//std::cout << "CreditsState::Draw" << std::endl;

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f(m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));

	m_system->m_window->draw(rect_fade);
}

std::string CreditsState::Next(){
	//std::cout << "CreditsState::next" << std::endl;
	return m_next;
}

bool CreditsState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}

bool CreditsState::isPaused()
{
	return m_paused;
}

bool CreditsState::isBase()
{
	return m_base;
}