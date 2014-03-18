// System.h

#pragma once
#include "System.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\RectangleShape.hpp"

#include "InputManager.h"
#include "AnimatedSprite.h"

#include "SpriteManager.h"
#include "SoundManager.h"
#include "FileManager.h"
#include "FontManager.h"

#include <iostream>

System::System()
{
	m_width = 1280;
	m_height = 720;

	m_title = "Haunted Light - BETA";

	m_fullscreen = false;
	m_borderless = false;
	m_vsync = false;
	m_debug = false;

	m_ticks = 0.f;
	m_fps = 0;

	m_video_modes = sf::VideoMode::getFullscreenModes();

	m_volume = .2f;

	m_window = nullptr;
	m_icon = nullptr;
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

	m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title,
		sf::Style::Titlebar | sf::Style::Close);
	if (m_window == nullptr)
		return false;

	/*
	if (!m_icon->loadFromFile("../data/Haunted_Light_Icon.png") )
	{
		m_window->setIcon(256,256,m_icon->getPixelsPtr());
		return EXIT_FAILURE;
	}*/

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

	m_load_parts = 7;
	m_load_current = 0;

	// LOADING SPRITES
	m_sprite_manager->addTexture("Menu/spr_menu_background.png");
	m_sprite_manager->addTexture("Menu/spr_candle.png");
	m_sprite_manager->addTexture("Menu/spr_candle_light.png");

	ProcessLoad();

	// LOAD ALL THE TEXTURES #############################################################

	// MAIN MENU
	
	m_sprite_manager->addTexture("Menu/spr_title.png");
	m_sprite_manager->addTexture("Menu/spr_candle_idle.png");
	m_sprite_manager->addTexture("Menu/spr_candle_blow.png");

	ProcessLoad();

	//---------------------BUTTON----------------
	m_sprite_manager->addTexture("Menu/spr_button_play.png");
	m_sprite_manager->addTexture("Menu/spr_button_credits.png");
	m_sprite_manager->addTexture("Menu/spr_button_quit.png");
	m_sprite_manager->addTexture("Menu/spr_button_options.png");

	ProcessLoad();

	//Options Menu
	//m_sprite_manager->addTexture("Options/spr_options_background.png");
	m_sprite_manager->addTexture("Options/spr_volume_low.png");
	m_sprite_manager->addTexture("Options/spr_volume_high.png");
	m_sprite_manager->addTexture("Options/spr_volume_bars.png");
	m_sprite_manager->addTexture("Options/spr_button_apply.png");
	m_sprite_manager->addTexture("Options/spr_button_return.png");
	m_sprite_manager->addTexture("Options/spr_button_resolution_low.png");
	m_sprite_manager->addTexture("Options/spr_button_resolution_high.png");
	m_sprite_manager->addTexture("Options/spr_checkbox.png");

	ProcessLoad();

	// GAME
	m_sprite_manager->addTexture("spr_cursor.png");
	m_sprite_manager->addTexture("Game/spr_sight.png");
	m_sprite_manager->addTexture("Game/darkness.png");
	m_sprite_manager->addTexture("Game/spr_wall_brick.png");
	m_sprite_manager->addTexture("Game/spr_floor.png");
	m_sprite_manager->addTexture("Game/spr_player_shadow.png");
	m_sprite_manager->addTexture("Game/spr_critter_walk.png");
	m_sprite_manager->addTexture("Game/spr_monster_big.png");

	ProcessLoad();

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

	m_sprite_manager->addTexture("Game/spr_pickaxe_pickup.png");
	sf::Texture* tex_pickaxe_pickup = m_sprite_manager->getTexture("Game/spr_pickaxe_pickup.png");
	tex_pickaxe_pickup->setSmooth(true);

	ProcessLoad();

	sf::Texture* tex_wall = m_sprite_manager->getTexture("Game/spr_wall_brick.png");
	//tex_wall->setSmooth(true);

	// LOAD ALL THE FONTS
	m_font_manager->addFont("pixel.ttf");
	m_font_manager->addFont("MTCORSVA.TTF");

	m_sound_manager = new SoundManager("../data/sounds/");

	ProcessLoad();

	//LOAD ALL THE SOUNDS
	m_sound_manager->addSoundBuffer("thud.wav");
	m_sound_manager->addSoundBuffer("snd_Main_Menu_blow_out_candle.wav");
	m_sound_manager->addSoundBuffer("snd_ambient_alarm.wav");
	m_sound_manager->addSoundBuffer("snd_big_monster_1.wav");
	m_sound_manager->addSoundBuffer("snd_big_monster_2.wav");
	m_sound_manager->addSoundBuffer("snd_big_monster_3.wav");
	m_sound_manager->addSoundBuffer("snd_critter_attack.wav");
	m_sound_manager->addSoundBuffer("msc_critter_walk.wav");
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

	ProcessLoad();

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

void System::ProcessLoad()
{
	m_window->clear(sf::Color::Black);

	float height = m_height / 80.f;
	float width = m_width / 3.f;

	// SCALE
	sf::Vector2f scale = sf::Vector2f((float)m_width/1280.f,(float)m_height/720.f);

	// BACKGROUND
	AnimatedSprite* background = m_sprite_manager->getSprite("Menu/spr_menu_background.png",0,0,1280,720);
	background->setScale(scale.x,scale.y);

	// CANDLE
	AnimatedSprite* spr_candle = m_sprite_manager->getSprite("Menu/spr_candle.png",0,0,410,410);
	spr_candle->setScale(scale.x,scale.y);
	spr_candle->setOrigin(205,205);
	spr_candle->setPosition(m_width/2, m_height/2 - 54.f*scale.y);

	// Candle light
	AnimatedSprite* spr_candle_light = m_sprite_manager->getSprite("Menu/spr_candle_light.png",0,0,124,124,6);
	spr_candle_light->setScale(scale.x,scale.y);
	spr_candle_light->setOrigin(72,72);
	spr_candle_light->setPosition(m_width/2 + 6*scale.x, m_height/2 - 54.f*scale.y + 24*scale.y);


	// BACKGROUND
	sf::RectangleShape loading_background(sf::Vector2f( (width/m_load_parts)*m_load_current, height));
	loading_background.setFillColor(sf::Color(255,255,255,128));
	loading_background.setPosition(sf::Vector2f(m_width / 3.f,(m_height/8.f)*7.f - height/2.f));

	// OUTLINE
	sf::RectangleShape loading_bar(sf::Vector2f( width, height));
	loading_bar.setFillColor(sf::Color(255,255,255,0));
	loading_bar.setOutlineColor(sf::Color(255,255,255,128));
	loading_bar.setOutlineThickness(2);
	loading_bar.setPosition(sf::Vector2f(m_width / 3.f,(m_height/8.f)*7.f - height/2.f));

	// BACKGROUND
	m_window->draw(*background);
	m_window->draw(*spr_candle);
	m_window->draw(*spr_candle_light);

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f( m_width, m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));
	m_window->draw(rect_fade);

	// BAR
	m_window->draw(loading_background);
	m_window->draw(loading_bar);

	m_window->display();

	m_load_current++;
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