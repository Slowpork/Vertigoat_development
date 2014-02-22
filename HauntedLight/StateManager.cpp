//StateManager.cpp


#include "StateManager.h"
#include "State.h"
#include <iostream>


StateManager::StateManager() 
{
	std::cout << "\n  Created StateManager\n  --------------------\n" << std::endl;

	m_current = nullptr;
	m_main = nullptr;
}

StateManager::~StateManager(){
	auto it = m_states.begin();
	while(it != m_states.end()) {
		delete (*it);
		//*it = nullptr;
		it++;
	}
}

void StateManager::setMain(const std::string _main)
{
	std::cout << "  Main State = " << _main << std::endl << std::endl;

	for(unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(_main)) {
			m_main = m_states[i];
			return;
		}
	}
}

void StateManager::Attach(State *state)
{

	m_states.push_back(state);
}

void StateManager::Update(float deltatime)
{
	if(m_current == nullptr) { return; }
	if(!m_current->Update(deltatime)) {
		ChangeState();
	}
}

void StateManager::Draw(){
	if(m_current == nullptr) { return; }
	if (m_main != nullptr) m_main->Draw();
	m_current->Draw();
}

void StateManager::SetState(const std::string &type) {
	std::cout << "\n  Initial State = " << type << std::endl;

	for(unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(type)) {
			m_current = m_states[i];
			return;
		}
	}
}

void StateManager::ChangeState(){
	std::string next = m_current->Next();
	if(m_current != nullptr) {

		if (m_current != m_main)
		m_current->Exit();

		m_current = nullptr;
	}

	for(unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(next)) {
			m_current = m_states[i];
			m_current->Enter();
			return;
		}
	}
}

bool StateManager::IsRunning() {
	return m_current !=nullptr;
}