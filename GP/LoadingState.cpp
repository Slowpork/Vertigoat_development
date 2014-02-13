//LoadingState.cpp

#include "stdafx.h"
#include "LoadingState.h"

LoadingState::LoadingState(System* _system)
{
	std::cout << "Created LoadingState" << std::endl;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool LoadingState::Enter(){
	std::cout << "LoadingState" << std::endl;
	return true;
}
void LoadingState::Exit(){
	std::cout << "LoadingState->";
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
	return "GameState";
}
bool LoadingState::IsType(const std::string &type){
	return type.compare("LoadingState") == 0;
}