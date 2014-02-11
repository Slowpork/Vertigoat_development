//OptionsState.cpp

#include "stdafx.h"
#include "OptionsState.h"
#include <iostream>

OptionsState::OptionsState(System* _system){
	m_system = _system;
	object_manager = new ObjectManager();

	std::cout << "OptionsState::OptionsState" << std::endl;
}

bool OptionsState::Enter(){
	std::cout << "OptionsState::Enter" << std::endl;
	return true;
}
void OptionsState::Exit(){
	std::cout << "OptionsState::Exit" << std::endl;
}
bool OptionsState::Update(float deltatime){
	std::cout << "OptionsState::Update" << std::endl;
	std::cout << "here be dragons, press anything pls " << std::endl;
	std::cin.ignore(1024, '\n');
	std::cin.get();
	return false;
}
void OptionsState::Draw(){
	std::cout << "OptionsState::Draw" << std::endl;

	object_manager->Draw(m_system->m_window);
}
std::string OptionsState::Next(){
	std::cout << "OptionsState::next" << std::endl;
	return "MenuState";
}
bool OptionsState::IsType(const std::string &type) {
	return type.compare("OptionsState") == 0;
}