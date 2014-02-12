// System.h

#include "stdafx.h"
#include "System.h"

System::System()
{
	m_width = 1280;
	m_height = 720;

	m_ticks = 0.f;

	m_window = nullptr;
	m_clock = nullptr;

	m_file_manager = nullptr;
	m_sprite_manager = nullptr;
	//m_sound_manager = nullptr;

	m_keyboard = nullptr;
	m_mouse = nullptr;
}

System::~System()
{

}

bool System::Init()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "Haunted Light - Pre-alpha");
	if (m_window == nullptr)
		return false;

	// VIEW
	m_view = new sf::View(sf::FloatRect(0,0,1280,720));
	m_view->setViewport(sf::FloatRect(0,0,1,1));
	//m_window->setView(*m_view);

	// SETTINGS
	//m_window->setVerticalSyncEnabled(true);
	m_window->setFramerateLimit(60);

	m_clock = new sf::Clock();

	m_file_manager = new FileManager();
	m_sprite_manager = new SpriteManager("../data/sprites/");

	// LOAD ALL THE TEXTURES
	m_sprite_manager->addTexture("player.png");
	m_sprite_manager->addTexture("curs.png");

	//m_sound_manager = new SoundManager();

	m_keyboard = new KeyboardObject();
	m_mouse = new MouseObject();

	return true;
}