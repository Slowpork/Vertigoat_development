//MenuState.cpp

#include "stdafx.h"

MenuState::MenuState(System* _system)
{
	m_system = _system;
	std::cout << "MenuState::MenuState" << std::endl;
	m_done = false;
}

bool MenuState::Enter(){
	
	std::cout << "MenuState::Enter" << std::endl;
	return true;
}

void MenuState::Exit(){
	std::cout << "MenuState::exit" << std::endl;
}

bool MenuState::Update(float deltatime){
	//std::cout << "MenuState::Update" << std::endl;
	
	/*
	std::cout << "[new] New game" << std::endl;
	std::cout << "[opt] Options" << std::endl;
	std::cout << "[quit] Quit" << std::endl;
	
	std::string choice;
	std::cin >> choice;
	if(choice.compare("new") == 0) {
		m_next_state = "GameState";
		m_done = true;
	}
	else if(choice.compare("opt") == 0) {
		m_next_state = "OptionState";
		m_done = true;
	}
	else if(choice.compare("quit") == 0) {
		m_next_state = "";
		m_done = true;
	};
	*/

	return true;
	
	return !m_done;
}

void MenuState::Draw(){
	//std::cout << "MenuState::Draw" << std::endl;

	if ( m_system->m_keyboard->IsDown(sf::Keyboard::Space))
	{
		sf::CircleShape shape(10);

		// set the shape color to green
		if (m_system->m_mouse->IsDown(Left))
			shape.setFillColor(sf::Color::Red);
		else if (m_system->m_mouse->IsDown(Right))
			shape.setFillColor(sf::Color::Blue);
		else
			shape.setFillColor(sf::Color::White);
		shape.setOrigin(10,10);
		shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(*m_system->m_window).x, sf::Mouse::getPosition(*m_system->m_window).y));

		m_system->m_window->draw(shape);
	}
}

std::string MenuState::Next(){
	std::cout << "MenuState::next" << std::endl;
	return m_next_state;
}

bool MenuState::IsType(const std::string &type) {

	std::cout << "MenuState::IsType" << std::endl;

	return type.compare("MenuState") == 0;
}