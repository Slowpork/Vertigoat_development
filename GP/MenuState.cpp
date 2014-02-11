//MenuState.cpp

#include "stdafx.h"

MenuState::MenuState(System* _system)
{
	m_system = _system;
	object_manager = new ObjectManager();

	std::cout << "MenuState::MenuState" << std::endl;
	m_done = false;

	pos = sf::Vector2f(1280/2,720/2);
}

bool MenuState::Enter(){
	
	std::cout << "MenuState::Enter" << std::endl;
	return true;
}

void MenuState::Exit(){
	std::cout << "MenuState::exit" << std::endl;
}

bool MenuState::Update(float _deltatime){
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

	//printf("woo");

	//std::cout << _deltatime << std::endl;

	//_deltatime = 0.05;

	pos.x += 64*_deltatime;
	
	return !m_done;
}

void MenuState::Draw(){
	//std::cout << "MenuState::Draw" << std::endl;

	//if ( m_system->m_keyboard->IsDown(sf::Keyboard::Space))
	//for(int i = 0; i < 100; i++)
	{
		sf::CircleShape shape(5);

		// set the shape color to green
		if (m_system->m_mouse->IsDown(Middle))
			shape.setFillColor(sf::Color::Red);
		else if (m_system->m_mouse->IsDown(Right))
			shape.setFillColor(sf::Color::Blue);
		else
			shape.setFillColor(sf::Color::White);
		shape.setOrigin(5,5);
		//shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(*m_system->m_window).x, sf::Mouse::getPosition(*m_system->m_window).y));
		shape.setPosition(pos);
		m_system->m_window->draw(shape);
	}

	object_manager->Draw(m_system->m_window);
}

std::string MenuState::Next(){
	std::cout << "MenuState::next" << std::endl;
	return m_next_state;
}

bool MenuState::IsType(const std::string &type) {

	std::cout << "MenuState::IsType" << std::endl;

	return type.compare("MenuState") == 0;
}