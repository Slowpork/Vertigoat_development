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

//	sf::RenderWindow window(sf::VideoMode(width, height), "Nånting spännande");
/*
	sf::Keyboard keyboard;

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(0, 255, 0));
	shape.setOrigin(100.f, 100.f);
	shape.setPosition(width/2, height/2);

	std::cout << shape.getOrigin().x << " " << shape.getOrigin().y;
	*/
/*

		window.clear(sf::Color(0x11, 0x22, 0x33, 0xff));
		window.draw(shape);
		window.display();
	}
*/
	manager.engine = this;
	manager.Attach(new MenuState);
	manager.Attach(new LoadingState);
	manager.Attach(new OptionsState);
	manager.Attach(new GameState);
	manager.SetState("MenuState");

	m_running = true;
	return true;
}

void Engine::runGame()
{
	while(m_running) 
	{
		manager.Update(m_deltatime);
		manager.Draw();
		updateDeltatime();
		updateEvents();
	}
}

void Engine::Cleanup()
{


	if(window != nullptr)
	{
	
	}


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
 