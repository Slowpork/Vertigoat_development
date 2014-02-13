//OptionsState.cpp

#include "stdafx.h"
#include "OptionsState.h"

OptionsState::OptionsState(System* _system)
{
	std::cout << "Created OptionsState" << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool OptionsState::Enter(){
	std::cout << "OptionsState::Enter" << std::endl;
	return true;
}
void OptionsState::Exit(){
	std::cout << "OptionsState::Exit" << std::endl;
}
bool OptionsState::Update(float deltatime){
	//std::cout << "OptionsState::Update" << std::endl;

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