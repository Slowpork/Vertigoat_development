//LoadingState.cpp

#include "stdafx.h"
#include "LoadingState.h"

LoadingState::LoadingState(System* _system){
	m_system = _system;
	object_manager = new ObjectManager();

	std::cout << "LoadingState::LoadingState" << std::endl;
}

bool LoadingState::Enter(){
	std::cout << "LoadingState::Enter" << std::endl;
	return true;
}
void LoadingState::Exit(){
	std::cout << "LoadingState::Exit" << std::endl;
}
bool LoadingState::Update(float deltatime){
	std::cout << "LoadingState::Update" << std::endl;
	return false;
}
void LoadingState::Draw(){
	std::cout << "LoadingState::Draw" << std::endl;

	object_manager->Draw(m_system->m_window);
}
std::string LoadingState::Next(){
	std::cout << "LoadingState::Next" << std::endl;
	return "MenuState";
}
bool LoadingState::IsType(const std::string &type){
	return type.compare("LoadingState") == 0;
}