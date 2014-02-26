//LoadingState.cpp

#include "LoadingState.h"

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

#include "Wall.h"
#include "PlayerObject.h"

#include "Collider.h"

LoadingState::LoadingState(System* _system)
{
	m_name = "LoadingState";
	m_next = "GameState";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool LoadingState::Enter(){
	//std::cout << m_name << std::endl;
	m_paused = false;
	return true;
}
void LoadingState::Exit(){
	//std::cout << "  " << m_name << "->";
}

void LoadingState::Pause()
{
	m_paused = true;
}

void LoadingState::Resume()
{
	m_paused = false;
}

bool LoadingState::Update(float deltatime){
	//std::cout << "LoadingState::Update" << std::endl;

	m_paused = true;
	return false;
}
void LoadingState::Draw(){
	//std::cout << "LoadingState::Draw" << std::endl;

	m_system->m_window->clear(sf::Color::Black);

	object_manager->Draw(m_system->m_window);
}
std::string LoadingState::Next(){
	//std::cout << "Goto GameState\n--" << std::endl;
	return m_next;
}
bool LoadingState::IsType(const std::string &type){
	return type.compare(m_name) == 0;
}

bool LoadingState::isPaused()
{
	return m_paused;
}

bool LoadingState::isBase()
{
	return m_base;
}