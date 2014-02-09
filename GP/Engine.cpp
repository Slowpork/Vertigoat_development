//Engine.cpp

#pragma once

#include "stdafx.h"

#include "FileManager.h"


Engine::Engine()
{
	window = nullptr;
	m_running = false;
	clock = nullptr;

	m_ticks = 0;
}

bool Engine::Init()
{
	clock = new sf::Clock;
	int width = 1024, height = 640;
	window = new sf::RenderWindow(sf::VideoMode(width, height), "Haunted Light");
	window->setVerticalSyncEnabled(true);

	FileManager file_manager;
	file_manager.Write("../bin/Awesome.txt", "#Yolo");

	state_manager.engine = this;
	state_manager.Attach(new MenuState);
	state_manager.Attach(new LoadingState);
	state_manager.Attach(new OptionsState);
	state_manager.Attach(new GameState);
	state_manager.SetState("MenuState");

	m_running = true;
	return true;
}

void Engine::runGame()
{
	while(m_running)
	{
		state_manager.Update(m_deltatime);
		state_manager.Draw();
		updateDeltatime();
		updateEvents();
	}
}

void Engine::Cleanup()
{

}

void Engine::updateDeltatime()
{
	sf::Time deltatime = clock->restart();
	
	float m_ticks = (float)deltatime.asMilliseconds();
}

void Engine::updateEvents()
{
	while(window->isOpen())
	{
		sf::Event event;
		while(window->pollEvent(event))
		{
			if(event.type == event.Closed)
			{
				window->close();
			}
		}

		if(keyboard->isKeyPressed(keyboard->Escape))
		{
			window->close();
		}
	}
}
 