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

#include <iostream>

System::System()
{
	m_width = 1280;
	m_height = 720;

	m_title = "Haunted Light - Pre Beta";

	m_fullscreen = false;
	m_borderless = false;
	m_vsync = false;
	m_debug = false;

	m_ticks = 0.f;
	m_fps = 0;

	m_video_modes = sf::VideoMode::getFullscreenModes();

	m_volume = .25f;

	m_window = nullptr;
	m_view = nullptr;
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
	delete m_window; m_window = nullptr;
	delete m_view; m_view = nullptr;
	delete m_clock; m_clock = nullptr;

	delete m_file_manager; m_file_manager = nullptr;
	delete m_sprite_manager; m_sprite_manager = nullptr;
	delete m_font_manager; m_font_manager = nullptr;
	delete m_sound_manager; m_sound_manager = nullptr;

	delete m_keyboard; m_keyboard = nullptr;
	delete m_mouse; m_mouse = nullptr;
}

bool System::Init()
{
	m_file_manager = new FileManager();

	if (!m_video_modes.empty())
	{
		bool found = false;
		for (unsigned i=0; i<m_video_modes.size(); i++)
		{
			/*
			if (m_video_modes[i].bitsPerPixel == 32)
			std::cout << m_video_modes[i].width 
			<< 'x' << m_video_modes[i].height 
			<< ' ' << m_video_modes[i].bitsPerPixel << std::endl;*/

			if (m_video_modes[i].width == m_width && m_video_modes[i].height == m_height)
			{
				found = true;
				break;
			}
		}

		// IF NOT SUPPORTED VIDEO MODE CHANGE TO DEFAULT 
		if (!found)
		{
			m_width = m_video_modes[0].width;
			m_height = m_video_modes[0].height;
		}
	}
	else
		return false;

	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), "Haunted Light - Alpha",
		sf::Style::Titlebar | sf::Style::Close);
	if (m_window == nullptr)
		return false;

	m_vsync = false;
	m_fullscreen = false;
	setVideoMode();

	// VIEW
	m_view = new sf::View(sf::FloatRect(0,0,(float)m_width,(float)m_height));
	m_view->setViewport(sf::FloatRect(0,0,1,1));
	//m_window->setView(*m_view);

	// BLACK INTITIAL SCREEN
	m_window->clear(sf::Color::Black);
	m_window->display();

	m_clock = new sf::Clock();

	m_sprite_manager = new SpriteManager("../data/sprites/");
	m_font_manager = new FontManager("../data/fonts/");

	// LOAD ALL THE TEXTURES #############################################################

	// MAIN MENU
	m_sprite_manager->addTexture("Menu/spr_menu_background.png");
	m_sprite_manager->addTexture("Menu/spr_title.png");
	m_sprite_manager->addTexture("Menu/spr_candle_light.png");
	m_sprite_manager->addTexture("Menu/spr_candle_idle.png");
	m_sprite_manager->addTexture("Menu/spr_candle_blow.png");
	m_sprite_manager->addTexture("Menu/spr_candle.png");

	//---------------------BUTTON----------------
	m_sprite_manager->addTexture("Menu/spr_button_play.png");
	//----------------------------------------------------

	//Options Menu
//	m_sprite_manager->addTexture("Options/spr_options_background.png");
	m_sprite_manager->addTexture("Options/spr_volume_low.png");

	// GAME
	m_sprite_manager->addTexture("curs.png");
	m_sprite_manager->addTexture("Game/darkness.png");
	m_sprite_manager->addTexture("Game/spr_wall_brick.png");
	m_sprite_manager->addTexture("Game/spr_floor.png");
	m_sprite_manager->addTexture("Game/spr_player_shadow.png");
	m_sprite_manager->addTexture("Game/spr_critter_walk.png");
	m_sprite_manager->addTexture("Game/spr_monster_big.png");

	sf::Texture* tex_critter = m_sprite_manager->getTexture("Game/spr_critter_walk.png");
	tex_critter->setSmooth(true);

	sf::Texture* tex_player_shadow = m_sprite_manager->getTexture("Game/spr_player_shadow.png");
	tex_player_shadow->setSmooth(true);

	m_sprite_manager->addTexture("Game/spr_matches_hud.png");
	sf::Texture* tex_matches_hud = m_sprite_manager->getTexture("Game/spr_matches_hud.png");
	tex_matches_hud->setSmooth(true);

	m_sprite_manager->addTexture("Game/spr_player_walk.png");
	sf::Texture* tex_player = m_sprite_manager->getTexture("Game/spr_player_walk.png");
	tex_player->setSmooth(true);

	m_sprite_manager->addTexture("Game/spr_player_run.png");
	sf::Texture* tex_player_run = m_sprite_manager->getTexture("Game/spr_player_run.png");
	tex_player->setSmooth(true);


	sf::Texture* tex_wall = m_sprite_manager->getTexture("Game/spr_wall_brick.png");
	tex_wall->setSmooth(true);

	// LOAD ALL THE FONTS
	m_font_manager->addFont("pixel.ttf");

	m_sound_manager = new SoundManager("../data/sounds/");

	//LOAD ALL THE SOUNDS
	m_sound_manager->addSoundBuffer("thud.wav");
	m_sound_manager->addSoundBuffer("snd_Main_Menu_blow_out_candle.wav");
	m_sound_manager->addSoundBuffer("snd_ambient_alarm.wav");
	m_sound_manager->addSoundBuffer("snd_big_monster_1.wav");
	m_sound_manager->addSoundBuffer("snd_big_monster_2.wav");
	m_sound_manager->addSoundBuffer("snd_big_monster_3.wav");
	m_sound_manager->addSoundBuffer("snd_critter_attack.wav");
	m_sound_manager->addSoundBuffer("snd_critter_walk.wav");
	m_sound_manager->addSoundBuffer("snd_Crunching_sound.wav");
	m_sound_manager->addSoundBuffer("snd_Door.wav");
	m_sound_manager->addSoundBuffer("snd_Equipment_selection.wav");
	m_sound_manager->addSoundBuffer("snd_Equipment_selection_2.wav");
	m_sound_manager->addSoundBuffer("snd_Game_Over_screen.wav");
	m_sound_manager->addSoundBuffer("snd_Mining_not_hitting_anything.wav");
	m_sound_manager->addSoundBuffer("snd_Mining_Pickaxe.wav");
	m_sound_manager->addSoundBuffer("snd_Mining_with_pebbles.wav");
	m_sound_manager->addSoundBuffer("snd_New_Game_button.wav"); ////////////////
	m_sound_manager->addSoundBuffer("snd_Pickup_Powerup.wav");
	m_sound_manager->addSoundBuffer("msc_Player_breathing.wav");
	m_sound_manager->addSoundBuffer("snd_Player_dies.wav");
	m_sound_manager->addSoundBuffer("snd_Player_Lighting_Candle.wav");
	m_sound_manager->addSoundBuffer("snd_Player_walk_test.wav");
	m_sound_manager->addSoundBuffer("snd_Start_Up_screen.wav");
	m_sound_manager->addSoundBuffer("snd_wall_monster_1.wav");
	m_sound_manager->addSoundBuffer("snd_wall_monster_2.wav");
	m_sound_manager->addSoundBuffer("snd_wall_monster_3.wav");
	m_sound_manager->addSoundBuffer("snd_wall_monster_4.wav");
	m_sound_manager->addSoundBuffer("snd_wall_monster_5.wav");



	m_keyboard = new KeyboardObject();
	m_mouse = new MouseObject();

	return true;
}

void System::setVideoMode()
{
	if (m_borderless)
	{
		m_width = m_video_modes[0].width;
		m_height = m_video_modes[0].height;
	}
	sf::VideoMode videomode = sf::VideoMode(m_width,m_height);

	if (m_fullscreen)
	m_window->create(videomode,m_title,sf::Style::Fullscreen);
	else
	{
		if (m_borderless)
		m_window->create(videomode,m_title,sf::Style::None);
		else
		m_window->create(videomode,m_title,sf::Style::Titlebar | sf::Style::Close);
	}

	if (m_vsync)
	{
		m_window->setFramerateLimit(0);
		m_window->setVerticalSyncEnabled(true);
	}
	else
	{
		m_window->setFramerateLimit(60);
		m_window->setVerticalSyncEnabled(false);
	}
	m_window->setMouseCursorVisible(false);
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

// Min 0, Max 1
float System::getVolume()
{
	return m_volume;
}

// Min 0, Max 1
void System::setVolume(float _newvolume)
{
	m_volume = _newvolume;
}