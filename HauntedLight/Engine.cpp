//Engine.cpp

#pragma once
#include "Engine.h"
#include "System.h"

#include "SFML\Graphics.hpp"

#include "FileManager.h"
#include "SpriteManager.h"
#include "InputManager.h"

#include "MenuState.h"
#include "LoadingState.h"
#include "OptionsState.h"
#include "GameState.h"
#include "CreditsState.h"
#include "PauseState.h"

#include "AnimatedSprite.h"

#include <iostream>

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

	// LOAD CURSOR & SIGHT
	spr_cursor = m_system->m_sprite_manager->getSprite("spr_cursor.png",0,0,16,16);
	spr_sight = m_system->m_sprite_manager->getSprite("Game/spr_sight.png",0,0,16,16);
	spr_sight->setOrigin(8,8);

	FileManager file_manager;
	file_manager.Write("../bin/Awesome.txt", "#Yolo");

	m_state_manager.Attach(new GameState(m_system));
	m_state_manager.Attach(new MenuState(m_system));
	m_state_manager.Attach(new LoadingState(m_system));
	m_state_manager.Attach(new OptionsState(m_system));
	m_state_manager.Attach(new CreditsState(m_system));
	m_state_manager.Attach(new PauseState(m_system));
	m_state_manager.SetState("MenuState");

	m_running = true;
	return true;
}

void Engine::Run()
{
	while(m_running)
	{
		// UPDATE
		updateDeltatime();
		m_system->setFps(m_fps);
		updateEvents();
		m_state_manager.Update(m_deltatime);

		if ( !m_state_manager.IsRunning())
		{
			m_running = false;
			break;
		}

		// DRAW 
		m_system->m_window->clear(sf::Color(0,0,0,255));
		m_state_manager.Draw();

		// CURSOR
		bool isState = m_state_manager.isState("GameState");
		if ( isState ) // GameState
		{
			spr_sight->setPosition((float)m_system->m_mouse->GetX(), (float)m_system->m_mouse->GetY());
			m_system->m_window->draw(*spr_sight);
		}
		else 
		{
			bool isState = m_state_manager.isState("CreditsState");

			if (!isState) // Not Credits
			{
				spr_cursor->setPosition((float)m_system->m_mouse->GetX(), (float)m_system->m_mouse->GetY());
				m_system->m_window->draw(*spr_cursor);
			}
		}

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
	if(m_deltatime > 0.1f)
		m_deltatime = 0.1f;

	// FPS
	m_fps = 1.f / m_deltatime;
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

			m_system->m_view->setSize(sf::Vector2f((float)event.size.width,(float)event.size.height));
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

	/*
	if ( m_system->m_mouse->GetX() != m_system->m_mouse->getPos().x && 
				 m_system->m_mouse->GetY() != m_system->m_mouse->getPos().y)
			std::cout << "Mouse Pos X: " << m_system->m_mouse->GetX()
				<< " Y: " << m_system->m_mouse->GetY() << " Pos X: " 
				<< m_system->m_mouse->getPos().x << " Y: " 
				<< m_system->m_mouse->getPos().y << std::endl;*/

	// GLOBAL MOUSE COORDINATES
	m_system->m_window->setView(*m_system->m_view);
	m_system->m_mouse->m_pos = m_system->m_window->mapPixelToCoords(sf::Vector2i(m_system->m_mouse->GetX(),m_system->m_mouse->GetY()));

	// ESCAPE TO QUIT
	if(m_system->m_keyboard->IsDownOnce(sf::Keyboard::Escape)){
		//m_running = false;
		//m_system->m_window->close();
	}

	// TOGGLE DEBUG
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::F1))
		m_system->setDebug(m_system->m_debug = !m_system->m_debug);
	
	// TOGGLE FULLSREEN
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::F11) 
		|| (m_system->m_keyboard->IsDown(sf::Keyboard::LAlt) && m_system->m_keyboard->IsDownOnce(sf::Keyboard::Return)) )
	{
		m_system->m_fullscreen = !m_system->m_fullscreen;
		m_system->setVideoMode();
	}
}
 