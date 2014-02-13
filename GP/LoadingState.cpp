//LoadingState.cpp

#include "stdafx.h"
#include "LoadingState.h"

LoadingState::LoadingState(System* _system)
{
	m_name = "LoadingState";
	m_next = "GameState";
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool LoadingState::Enter(){
	std::cout << m_name << std::endl;
	return true;
}
void LoadingState::Exit(){
	std::cout << "  " << m_name << "->";
}
bool LoadingState::Update(float deltatime){
	//std::cout << "LoadingState::Update" << std::endl;

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