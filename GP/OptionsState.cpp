//OptionsState.cpp

#include "stdafx.h"
#include "OptionsState.h"

OptionsState::OptionsState(System* _system)
{
	m_name = "OptionsState";
	m_next = "MenuState";
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool OptionsState::Enter(){
	std::cout << m_name << std::endl;
	return true;
}
void OptionsState::Exit(){
	std::cout << "  " << m_name << "->";
}
bool OptionsState::Update(float deltatime){
	//std::cout << "OptionsState::Update" << std::endl;

	return false;
}
void OptionsState::Draw(){
	//std::cout << "OptionsState::Draw" << std::endl;

	object_manager->Draw(m_system->m_window);
}
std::string OptionsState::Next(){
	//std::cout << "OptionsState::next" << std::endl;
	return "MenuState";
}
bool OptionsState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}