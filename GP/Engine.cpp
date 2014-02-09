//Engine.cpp

#pragma once
#include "stdafx.h"

Engine::Engine()
{
	m_running = false;
}

bool Engine::Init()
{
	m_system = new System();

	if (!m_system->Init())
		return false;

	FileManager file_manager;
	file_manager.Write("../bin/Awesome.txt", "#Yolo");

	state_manager.Attach(new MenuState(m_system));
	state_manager.Attach(new LoadingState(m_system));
	state_manager.Attach(new OptionsState(m_system));
	state_manager.Attach(new GameState(m_system));
	state_manager.SetState("MenuState");

	m_running = true;
	return true;
}

void Engine::Run()
{
	while(m_running)
	{
		// UPDATE
		updateDeltatime();
		updateEvents();
		state_manager.Update(m_deltatime);

		// DRAW 
		m_system->m_window->clear(sf::Color::Black);
		state_manager.Draw();
		m_system->m_window->display();

		m_system->m_keyboard->PostUpdate();
		m_system->m_mouse->PostUpdate();
	}
}

void Engine::Cleanup()
{
	delete m_system;
	m_system = nullptr;
}

void Engine::updateDeltatime()
{
	sf::Time deltatime = m_system->m_clock->restart();
	
	m_system->m_ticks = (float)deltatime.asMilliseconds();
}

void Engine::updateEvents()
{
	sf::Event event;
	while(m_system->m_window->pollEvent(event))
	{
		if(event.type == event.Closed){
			m_system->m_window->close();
			m_running = false;
		}

		// KEYBOARD
		if (event.type == sf::Event::KeyPressed){
			m_system->m_keyboard->current[event.key.code] = true;
		}
		if (event.type == sf::Event::KeyReleased){
			m_system->m_keyboard->current[event.key.code] = false;
		}
		
		// MOUSE
		if (event.type == sf::Event::MouseButtonPressed){
			m_system->m_mouse->current[event.mouseButton.button] = true;
		}
		if (event.type == sf::Event::MouseButtonReleased){
			m_system->m_mouse->current[event.mouseButton.button] = false;
		}
		
	}

	if(m_system->m_keyboard->IsDownOnce(sf::Keyboard::Escape)){
		m_system->m_window->close();
		m_running = false;
	}
}
 