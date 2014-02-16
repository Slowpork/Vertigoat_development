// System.h

#pragma once
#include "System.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Texture.hpp"

#include "InputManager.h"

#include "SpriteManager.h"
#include "FileManager.h"

System::System()
{
	m_width = 1280;
	m_height = 720;

	m_fullscreen = false;
	m_debug = false;

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
	m_view = new sf::View(sf::FloatRect(0,0,m_width,m_height));
	m_view->setViewport(sf::FloatRect(0,0,1,1));
	//m_window->setView(*m_view);

	// SETTINGS
	//m_window->setVerticalSyncEnabled(true);
	m_window->setFramerateLimit(60);
	m_window->setMouseCursorVisible(false);

	// BLACK INTITIAL SCREEN
	m_window->clear(sf::Color::Black);
	m_window->display();

	m_clock = new sf::Clock();

	m_file_manager = new FileManager();
	m_sprite_manager = new SpriteManager("../data/sprites/");

	// LOAD ALL THE TEXTURES
	m_sprite_manager->addTexture("player.png");
	sf::Texture* tex_player = m_sprite_manager->getTexture("player.png");
	tex_player->setSmooth(true);

	m_sprite_manager->addTexture("curs.png");
	m_sprite_manager->addTexture("darkness.png");
	m_sprite_manager->addTexture("wall.png");
	m_sprite_manager->addTexture("floor.png");
	m_sprite_manager->addTexture("monster.png");
	m_sprite_manager->addTexture("player_anim.png");
	m_sprite_manager->addTexture("player_walk.png");
	sf::Texture* tex_wall = m_sprite_manager->getTexture("wall.png");
	tex_wall->setSmooth(true);

	//m_sound_manager = new SoundManager();

	m_keyboard = new KeyboardObject();
	m_mouse = new MouseObject();

	return true;
}