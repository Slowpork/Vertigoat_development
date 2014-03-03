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

#include "Wall.h"
#include "PlayerObject.h"
#include "AnimatedSprite.h"

#include "Collider.h"

OptionsState::OptionsState(System* _system)
{
	m_name = "OptionsState";
	m_next = "MenuState";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
}

bool OptionsState::Enter(){
	std::cout << m_name << std::endl;

	object_manager = new ObjectManager();

	sf::Vector2f scale = sf::Vector2f((float)m_system->m_width/1280.f,(float)m_system->m_height/720.f);

	//Background
	spr_background = m_system->m_sprite_manager->getSprite("spr_options_background.png",0,0,1288,720);
	spr_background->setScale(scale.x,scale.y);

	return true;
}
void OptionsState::Exit()
{
	std::cout << "  " << m_name << "->";

	delete spr_background;
	spr_background = nullptr;

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
	spr_background->play(_deltatime/2);

	return false;
}
void OptionsState::Draw(){
	//std::cout << "OptionsState::Draw" << std::endl;

	m_system->m_window->setView(m_system->m_window->getDefaultView());

	m_system->m_window->draw(*spr_background);

	object_manager->Draw(m_system->m_window);
}
std::string OptionsState::Next(){
	//std::cout << "OptionsState::next" << std::endl;
	return "MenuState";
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