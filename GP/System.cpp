// System.h

#include "stdafx.h"
#include "System.h"
#include "InputManager.h"

System::System()
{
	m_width = 1280;
	m_height = 720;

	m_ticks = 0.f;

	m_window = nullptr;
	m_clock = nullptr;

	m_file_manager = nullptr;
	//m_sound_manager = nullptr;

	m_keyboard = nullptr;
	m_mouse = nullptr;
}

System::~System()
{

}

bool System::Init()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "Haunted Light");
	if (m_window == nullptr)
		return false;

	//m_window->setFramerateLimit(60);

	m_clock = new sf::Clock();

	m_file_manager = new FileManager();
	//m_sound_manager = new SoundManager();

	m_keyboard = new Keyboard();
	m_mouse = new Mouse();
}