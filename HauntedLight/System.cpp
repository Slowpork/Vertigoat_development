// System.h

#pragma once
#include "System.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\RectangleShape.hpp"

#include "InputManager.h"

#include "SpriteManager.h"
#include "SoundManager.h"
#include "FileManager.h"
#include "FontManager.h"


System::System()
{
	m_width = 1920;
	m_height = 1080;

	m_fullscreen = false;
	m_debug = false;

	m_ticks = 0.f;
	m_fps = 0;

	m_window = nullptr;
	m_clock = nullptr;

	m_file_manager = nullptr;
	m_sprite_manager = nullptr;
	m_font_manager = nullptr;
	m_sound_manager = nullptr;

	m_keyboard = nullptr;
	m_mouse = nullptr;
}

System::~System()
{
	
}

bool System::Init()
{
	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "Haunted Light - Alpha");
	if (m_window == nullptr)
		return false;

	// VIEW
	m_view = new sf::View(sf::FloatRect(0,0,(float)m_width,(float)m_height));
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
	m_font_manager = new FontManager("../data/fonts/");

	// LOAD ALL THE TEXTURES
	m_sprite_manager->addTexture("curs.png");
	m_sprite_manager->addTexture("darkness.png");
	m_sprite_manager->addTexture("wall.png");
	m_sprite_manager->addTexture("spr_floor.png");

	m_sprite_manager->addTexture("spr_matches_hud.png");
	sf::Texture* tex_matches_hud = m_sprite_manager->getTexture("spr_matches_hud.png");
	tex_matches_hud->setSmooth(true);

	m_sprite_manager->addTexture("spr_player_walk.png");
	sf::Texture* tex_player = m_sprite_manager->getTexture("spr_player_walk.png");
	tex_player->setSmooth(true);

	m_sprite_manager->addTexture("spr_player_run.png");
	sf::Texture* tex_player_run = m_sprite_manager->getTexture("spr_player_run.png");
	tex_player->setSmooth(true);


	sf::Texture* tex_wall = m_sprite_manager->getTexture("wall.png");
	tex_wall->setSmooth(true);

	// LOAD ALL THE FONTS
	m_font_manager->addFont("pixel.ttf");

	m_sound_manager = new SoundManager("../data/sounds/");

	//LOAD ALL THE SOUNDS
	m_sound_manager->addSoundBuffer("cow_bell.wav");
	m_sound_manager->addSoundBuffer("thud.wav");

	m_keyboard = new KeyboardObject();
	m_mouse = new MouseObject();

	return true;
}

void System::drawDebugRect(sf::Vector2f _pos, sf::Vector2f _size)
{
	sf::RectangleShape rect_player_box(sf::Vector2f( _size.x, _size.y));
	rect_player_box.setOrigin(
		rect_player_box.getLocalBounds().width/2,
		rect_player_box.getLocalBounds().height/2);
	rect_player_box.setFillColor(sf::Color(0,0,0,0));
	rect_player_box.setOutlineColor(sf::Color(255,0,0,128));
	rect_player_box.setOutlineThickness(2);
	rect_player_box.setPosition(_pos);

	m_window->draw(rect_player_box);
}

void System::setDebug(bool _fps)
{
	m_debug = _fps;
}

void System::setFps(int _fps)
{
	m_fps = _fps;
}

int System::getFps()
{
	return m_fps;
}