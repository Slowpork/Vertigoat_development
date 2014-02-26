//StateManager.cpp


#include "StateManager.h"
#include "State.h"
#include <iostream>


StateManager::StateManager() 
{
	std::cout << "\n  Created StateManager\n  --------------------\n" << std::endl;

	//m_current = nullptr;
}

StateManager::~StateManager()
{
	auto it = m_states.begin();
	while(it != m_states.end()) {
		delete *it;
		//*it = nullptr;
		it++;
	}
}

void StateManager::Attach(State *state)
{
	m_states.push_back(state);
}

void StateManager::Update(float _deltatime)
{
	if (!m_current.empty())
	{
		for(auto current: m_current)
		{
			if (!current->isPaused())
			{
				//if (current->IsType("GameState"))
				//std::cout << "!" << std::endl;
				if ( !current->Update(_deltatime))
				{
					ChangeState();
					return;
				}
			}
		}
	}
	/*
	if(m_current == nullptr) { return; }
	if(!m_current->Update(deltatime)) {
		ChangeState();
	}*/
}

void StateManager::Draw()
{
	bool draw = false;
	if (!m_current.empty())
	{
		for(auto current: m_current)
		{
			if (draw || current->isBase())
			{
				draw = true;
				current->Draw();
			}
		}
	}
	else
	return;
	
	/*
	if(m_current == nullptr) { return; }
	m_current->Draw();
	*/
}

void StateManager::SetState(const std::string &type)
{
	//std::cout << "\n  Initial State = " << type << std::endl;
	std::cout << "\n  SetState: " << type << std::endl;

	for(unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(type)) {
			//m_current = m_states[i];
			m_current.push_back(m_states[i]);
			m_current.back()->Enter();
			return;
		}
	}
}

void StateManager::ChangeState()
{
	// GET NEXT
	std::string next = "";
	if (!m_current.empty())
	{
		next = m_current.back()->Next();
		if ( next == "") // Return to previous state
		{
			m_current.back()->Exit();
			m_current.pop_back();
			
			if (!m_current.empty())
			{
				if (m_current.back()->isPaused())
				m_current.back()->Resume();
			}
			return;
		}
		else if ( !m_current.back()->isPaused()) // Reset states to defined
		{
			for(auto& current: m_current)
			{
				current->Exit();
			}
			m_current.clear();
			
			SetState(next);
			return;
		}
		else // Goto another state pausing the current one
		SetState(next);
	}

	/*
	// SET NEXT
	if (next != "")
	{
		for(unsigned int i = 0; i < m_states.size(); i++) 
		{
			if(m_states[i]->IsType(next)) 
			{
				m_current.push_back(m_states[i]);
				m_current.back()->Enter();
				//m_current = m_states[i];
				//m_current->Enter();
				return;
			}
		}
	}*/
}

bool StateManager::IsRunning()
{
	//return m_current !=nullptr;
	return !m_current.empty();
}