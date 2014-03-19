//StateManager.cpp


#include "StateManager.h"
#include "State.h"
#include <iostream>

/* STATE RULES

  *RETURN
   If state is left without m_next value...then it returns to the previous one.

  *OPEN MENU
   If state is left with a m_next value and is paused....then it keeps the previous 
   one in the background as the rendering base.

  *RESET AND RETURN TO...
   If state is left with a m_next value and isn't paused...then clear m_current and 
   restart at the next state.
 
*/

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
		*it = nullptr;
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
				if ( !current->Update(_deltatime))
				{
					ChangeState();
					return;
				}
			}
		}
	}
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
}

void StateManager::SetState(const std::string &type)
{
	//std::cout << "\n  Initial State = " << type << std::endl;
	std::cout << "\n  SetState: " << type << std::endl;

	for(unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(type)) {
			m_current.push_back(m_states[i]);
			m_current.back()->Enter();
			return;
		}
	}
}

bool StateManager::isState(std::string _state)
{
	if (!m_current.empty())
	{
		for(auto current: m_current)
		{
			if (!current->isPaused())
			{
				return current->IsType(_state);
			}
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
}

bool StateManager::IsRunning()
{
	//return m_current !=nullptr;
	return !m_current.empty();
}