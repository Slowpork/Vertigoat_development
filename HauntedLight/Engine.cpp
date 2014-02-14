//Engine.cpp

#pragma once
#include "Engine.h"
#include "System.h"

#include "FileManager.h"

#include "MenuState.h"
#include "LoadingState.h"
#include "OptionsState.h"
#include "GameState.h"

#include "InputManager.h"

#include "SFML\Graphics.hpp"

Engine::Engine()
{
	m_running = false;
	m_deltatime = 0.f;
	m_fps = 10.f;
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
	state_manager.SetState("LoadingState");

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

		if ( !state_manager.IsRunning())
			m_running = false;

		// DRAW 
		m_system->m_window->clear(/*sf::Color(44,29,23)*/sf::Color::Black);
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
	// DELTATIME
	m_deltatime = m_system->m_clock->restart().asSeconds();

	// FPS
	m_fps = 1.f / m_deltatime;
	//std::cout << m_fps << std::endl;
}

void Engine::updateEvents()
{
	sf::Event event;
	while(m_system->m_window->pollEvent(event))
	{
		// PRESS CLOSE TO QUIT
		if (event.type == event.Closed){
			m_system->m_window->close();
			m_running = false;
		}

		if (event.type == event.Resized)
		{
			m_system->m_view = new sf::View();

			m_system->m_view->setSize(sf::Vector2f(event.size.width,event.size.height));
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

		if (event.type == sf::Event::MouseMoved)
		{
			m_system->m_mouse->x = event.mouseMove.x;
			m_system->m_mouse->y = event.mouseMove.y;
			
			
		}
	}

	/*if ( m_system->m_mouse->GetX() != m_system->m_mouse->getPos().x && 
				 m_system->m_mouse->GetY() != m_system->m_mouse->getPos().y)
			std::cout << "Mouse Pix X: " << m_system->m_mouse->GetX()
				<< " Y: " << m_system->m_mouse->GetY() << " Pos X: " 
				<< m_system->m_mouse->getPos().x << " Y: " 
				<< m_system->m_mouse->getPos().y << std::endl;*/

	// GLOBAL MOUSE COORDINATES
	m_system->m_window->setView(*m_system->m_view);
	m_system->m_mouse->m_pos = m_system->m_window->mapPixelToCoords(sf::Vector2i(m_system->m_mouse->GetX(),m_system->m_mouse->GetY()));

	// ESCAPE TO QUIT
	if(m_system->m_keyboard->IsDownOnce(sf::Keyboard::Escape)){
		m_system->m_window->close();
		m_running = false;
	}

	// TOGGLE DEBUG
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
		m_system->m_debug = !m_system->m_debug;
	}

	
	// TOGGLE FULLSREEN
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::F11) 
		|| (m_system->m_keyboard->IsDown(sf::Keyboard::LAlt) && m_system->m_keyboard->IsDownOnce(sf::Keyboard::Return)) )
	{
		m_system->m_fullscreen = !m_system->m_fullscreen;

		m_system->m_window->close();
		delete m_system->m_window;

		if (m_system->m_fullscreen)
		m_system->m_window = new sf::RenderWindow(sf::VideoMode(m_system->m_width,m_system->m_height), "Haunted Light - Pre-alpha", sf::Style::Fullscreen);
		else
		m_system->m_window = new sf::RenderWindow(sf::VideoMode(m_system->m_width,m_system->m_height), "Haunted Light - Pre-alpha", sf::Style::Default);
		
		m_system->m_window->setFramerateLimit(60);
		m_system->m_window->setMouseCursorVisible(false);
	}
}
 