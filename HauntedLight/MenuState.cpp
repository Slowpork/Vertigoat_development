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

#include "Wall.h"
#include "PlayerObject.h"

#include "Collider.h"

MenuState::MenuState(System* _system)
{
	m_name = "MenuState";
	m_next = "LoadingState";
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
	
	m_done = false;
}

bool MenuState::Enter()
{
	std::cout << m_name << std::endl;
	return true;
}

void MenuState::Exit(){
	std::cout << "  " << m_name << "->";
}

bool MenuState::Update(float _deltatime){
	//std::cout << "MenuState::Update" << std::endl;
	
	return !m_done;
}

void MenuState::Draw(){
	//std::cout << "MenuState::Draw" << std::endl;
}

std::string MenuState::Next(){
	//std::cout << "MenuState::next" << std::endl;
	return m_next;
}

bool MenuState::IsType(const std::string &type) {

	//std::cout << "MenuState::IsType" << std::endl;

	return type.compare(m_name) == 0;
}