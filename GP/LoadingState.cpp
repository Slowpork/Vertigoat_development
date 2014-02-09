//LoadingState.cpp

#include "stdafx.h"
#include "LoadingState.h"
#include <iostream>

LoadingState::LoadingState(System* _system){
	m_system = _system;
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
}
std::string LoadingState::Next(){
	std::cout << "LoadingState::Next" << std::endl;
	return "MenuState";
}
bool LoadingState::IsType(const std::string &type){
	return type.compare("LoadingState") == 0;
}