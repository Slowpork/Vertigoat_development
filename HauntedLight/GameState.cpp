//GameState.cpp

#include "Gamestate.h"
#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\View.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\Graphics\CircleShape.hpp"

#include "SFML\Window\Keyboard.hpp"

#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "SFML\Audio\Music.hpp"

#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "SFML\Audio\Music.hpp"

#include "System.h"

#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "FontManager.h"

#include "LightSystem.h"
#include "LevelSystem.h"

#include "Random.h"

#include "Wall.h"
#include "PlayerObject.h"

#include "AnimatedSprite.h"
#include "Collider.h"

void addWall(sf::Vector2f _pos);

GameState::GameState(System* _system)
{
	m_name = "GameState";
	m_next = "MenuState";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
}

bool GameState::Enter()
{
	//std::cout << m_name << std::endl;
	m_base = true;
	m_paused = false;

	m_object_manager = new ObjectManager();

	m_level_system = new LevelSystem(m_object_manager, m_system->m_sprite_manager);

	m_collision_manager = new CollisionManager(m_object_manager);

	m_light_system = new LightSystem(m_system->m_window, m_system->m_view, m_object_manager);

	m_timer = 0.f;

	m_view_beat = Math::PI_HALF;
	m_view_beat = 0.f;

	sf::Vector2f scale = sf::Vector2f((float)m_system->m_width/1280.f,(float)m_system->m_height/720.f);

	// SOUNDS
	snd_thud = m_system->m_sound_manager->getSound("thud.wav");
	snd_thud->setVolume(25.f);

	music_main = m_system->m_sound_manager->getMusic("music.wav");
	music_main->setVolume(25.f);
	music_main->setLoop(true);
	//music_main->play();

	// FONTS
	fnt_small =  m_system->m_font_manager->getFont("pixel.ttf");

	// SPRITES
	AnimatedSprite* spr_player = m_system->m_sprite_manager->getSprite("Game/spr_player_walk.png",0,0,128,128,8);
	spr_player->setScale(.5,.5);
	AnimatedSprite* spr_player_run = m_system->m_sprite_manager->getSprite("Game/spr_player_run.png",0,0,132,132,12);
	spr_player_run->setScale(.5,.5);
	spr_floor = m_system->m_sprite_manager->getSprite("Game/spr_floor.png",0,0,400,400);

	spr_matches_hud = m_system->m_sprite_manager->getSprite("Game/spr_matches_hud.png",0,0,128,128,6);
	spr_matches_hud->setScale(.75f*scale.x,.75f*scale.y);
	spr_matches_hud->setColor(sf::Color(255,255,255,128));
	spr_matches_hud->setPosition((float)m_system->m_width - 128.f*1.5f*scale.x,(float)m_system->m_height - 128.f*scale.y);

	spr_player_shadow = m_system->m_sprite_manager->getSprite("Game/spr_player_shadow.png",0,0,960,1080);
	spr_player_shadow->setOrigin(960.f,540.f);

	spr_critter = m_system->m_sprite_manager->getSprite("Game/spr_critter_walk.png",0,0,128,128,7);
	spr_critter->setPosition(640,640);
	//spr_critter->setRotation(270);

	spr_darkness = m_system->m_sprite_manager->getSprite("Game/darkness.png",0,0,1280,720);
	spr_darkness->setOrigin(1280/2,720/2);
	spr_darkness->setScale(scale.x,scale.y);
	spr_darkness->setPosition((float)m_system->m_width/2,(float)m_system->m_height/2);

	
	// WALLS
	const float SIZE = 128;

	bool map[15][25] = 
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	int count = 0;

	for(int Y = 0; Y < 15; Y++)
	{
		for(int X = 0; X < 25; X++)
		{
			if (map[Y][X])
			{
				addWall(sf::Vector2f(SIZE*X,SIZE*Y));
				count++;
			}
		}
	}

	//std::cout << "  " << count;

	//std::cout << "\n";

	Collider* col_player = new Collider(sf::Vector2f(0,0),sf::Vector2f(96,96));

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	player->setPosition(sf::Vector2f(1280/2,720/2));
	player->setSprites(spr_player_run, spr_player_run);

	m_light_system->setBounds(sf::Vector2f(0,0),sf::Vector2f(3584,3584));
	m_light_system->update();

	return true;
}

void GameState::Exit(){
	std::cout << "  " << m_name << "->";

	// REMOVE SPRITES
	delete spr_floor; spr_floor = nullptr;
	delete spr_matches_hud; spr_matches_hud = nullptr;
	delete spr_darkness; spr_darkness = nullptr;

	delete player; player = nullptr;

	delete m_collision_manager; m_collision_manager = nullptr;
	delete m_light_system; m_light_system = nullptr;

	m_object_manager->Cleanup();
	delete m_object_manager; m_object_manager = nullptr;
}

void GameState::Pause()
{
	m_paused = true;

	std::cout << "  II PAUSED" << std::endl;
}

void GameState::Resume()
{
	m_paused = false;
}

void GameState::addWall(sf::Vector2f _pos)
{
	AnimatedSprite* spr_wall = m_system->m_sprite_manager->getSprite(
		"Game/wall.png",0,0,128,128);
	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall* wall = new Wall(spr_wall,col_wall);
	wall->setPosition(_pos);
	m_object_manager->Add(wall,5);
}

void GameState::viewScale(float _deltatime)
{
	float tracking = player->getSpeed();

	if (tracking == 0.92f)
	{
		if (m_view_beat > 0) 
		m_view_beat -= _deltatime/2;
		else
			m_view_beat = 0.f;
	}
	else
	{
		if (m_view_beat < 1)
		m_view_beat += _deltatime;
		else
			m_view_beat = 1.f;
	}

	if (m_view_beat > 1.f)
		m_view_beat = 1.f;
	if (m_view_beat < 0.2f)
		m_view_beat = 0.2f;

	float base_scale = 1280.f/(float)m_system->m_width;

	float factor = abs(sin(m_timer));
	m_light_system->setLightBrightness((m_view_beat*85.f + factor*15.f)*player->getLight());

	float scalefactor = (base_scale + m_view_beat*.5f);

	//std::cout << base_scale << std::endl;

	m_system->m_view->setSize(sf::Vector2f(m_system->m_width*scalefactor,m_system->m_height*scalefactor));
}

void GameState::FlickerLight(float _deltatime)
{
	if (player->hasCandle())
	m_timer += _deltatime*5;

	if (Random::between(0,50) == 0)
	{
		//m_timer = 0.f;
	}

	float factor = abs(sin(m_timer));

	float angle = player->getSprite()->getRotation() * (Math::PI/180);
	sf::Vector2f light_pos;
	float x_offset = 70.f * player->getSprite()->getScale().x;
	float y_offset = 25.f * player->getSprite()->getScale().y;
	
	if ( player->hasCandle() )
	{
		light_pos.x = x_offset * cos( angle ) - y_offset * sin( angle );
		light_pos.y = x_offset * sin( angle ) + y_offset * cos( angle );
	}

	m_light_system->setLightLocation(
		light_pos.x + player->getPosition().x - 5.f*factor + 10.f*factor,
		light_pos.y + player->getPosition().y - 5.f*factor + 10.f*factor);

	/*
	m_light_system->setLightLocation(
		player->getPosition().x - 5.f*factor + 10.f*factor,
		player->getPosition().y - 5.f*factor + 10.f*factor);*/
}

void GameState::drawFloor()
{
	const int floor_size = 400;
	sf::Vector2f view_pos = sf::Vector2f(
		m_system->m_view->getCenter().x - m_system->m_view->getSize().x/2,
		m_system->m_view->getCenter().y - m_system->m_view->getSize().y/2);

	sf::Vector2f mod_view_pos = sf::Vector2f(
		view_pos.x - (float)((int)view_pos.x % floor_size),
		view_pos.y - (float)((int)view_pos.y % floor_size));

	view_pos = mod_view_pos;
	view_pos.x -= floor_size;
	view_pos.y -= floor_size;

	for(float X = view_pos.x; X < view_pos.x + m_system->m_view->getSize().x + floor_size*2; X += floor_size)
	{
		for(float Y = view_pos.y; Y < view_pos.y + m_system->m_view->getSize().y + floor_size*2; Y += floor_size)
		{
			spr_floor->setPosition(
				X,
				Y);
			m_system->m_window->draw(*spr_floor, sf::BlendMultiply);
		}
	}
}

void GameState::playerCollision()
{
	sf::Vector2f offset;
	if (m_collision_manager->checkCollision(player->getCollider(),offset))
	{
		if (offset.x > 0.0f)
		{
			player->setVelocity(sf::Vector2f(0,player->getVelocity().y));
		}
		else if (offset.x < 0.0f)
		{
			player->setVelocity(sf::Vector2f(0,player->getVelocity().y));
		}

		if (offset.y > 0.0f)
		{
			player->setVelocity(sf::Vector2f(player->getVelocity().x,0));
		}
		else if (offset.y < 0.0f)
		{
			player->setVelocity(sf::Vector2f(player->getVelocity().x,0));
		}
		
		player->setPosition(player->getPosition() + offset);
	}
}

bool GameState::Update(float _deltatime){
	//std::cout << "GameState::Update" << std::endl;
	
	playerCollision();

	player->Update(_deltatime);
	m_level_system->Update(player->getPosition(), player->getPosition());

	spr_critter->play(_deltatime);

	viewScale(_deltatime);

	FlickerLight(_deltatime);
	m_light_system->logic(player->getPosition());
	spr_player_shadow->setPosition(player->getPosition());
	spr_player_shadow->turnToPoint(m_light_system->getLightLocation());
	
	// MOVE VIEW
	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);
	
	if (m_system->m_mouse->IsDownOnce(Left))
	{
		int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
		if ( ID == -1)
		{
			snd_thud->play();
			addWall(sf::Vector2f(
				m_system->m_mouse->getPos().x - ((int)m_system->m_mouse->getPos().x % 128),
				m_system->m_mouse->getPos().y - ((int)m_system->m_mouse->getPos().y % 128)));
			m_light_system->update();
		}
	}
	else if (m_system->m_mouse->IsDownOnce(Right)) // HIT WALL
	{
		int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
		if ( ID != -1)
		{
			GameObject* go = m_object_manager->getObject(ID);
			if (go != nullptr)
			{
				//if (static_cast<Wall*> (go)->hit())
					m_object_manager->destroy(ID);
			}
		}
		m_light_system->update();
	}

	if (!m_system->m_keyboard->IsDownOnce(sf::Keyboard::P))
	return true;
	else
	{
		m_next = "PauseState";
		Pause();
		return false;
	}
}

void GameState::Draw()
{
	const float brightness = m_light_system->getLightBrightness();

	// GAME-WORLD #################################
	m_system->m_window->setView(*m_system->m_view);

	m_light_system->Draw(player->getPosition());

	// PLAYER SHADOW
	if (player->hasCandle() )
	{
		spr_player_shadow->setColor(sf::Color(255,255,255,(int)brightness));
		//std::cout << m_light_system->getLightBrightness() << std::endl;
		m_system->m_window->draw(*spr_player_shadow);
	}
	
	// FLOOR
	drawFloor();

	// PLAYER
	player->getSprite()->setColor(sf::Color((int)m_light_system->getLightBrightness()
		,(int)m_light_system->getLightBrightness(),(int)m_light_system->getLightBrightness(),255));
	m_system->m_window->draw(*player->getSprite());

	m_system->m_window->draw(*spr_critter);

	// OBJECTS
	m_object_manager->setActiveDepth(5,5);
	m_object_manager->Draw(m_system->m_window, brightness);

	// PLAYER COLLISION-BOX
	if (m_system->m_debug)
	{
		m_system->drawDebugRect(player->getPosition(),
			sf::Vector2f(player->getCollider()->m_ext.x,
						player->getCollider()->m_ext.y));

		m_system->drawDebugRect(m_light_system->getLightLocation(),
			sf::Vector2f(4,4));
	}

	// INTERFACE ##################################
	m_system->m_window->setView(m_system->m_window->getDefaultView());
	
	// DARKNESS
	m_system->m_window->draw(*spr_darkness);

	// MATCHES
	spr_matches_hud->setFrame(player->getMatches());
	m_system->m_window->draw(*spr_matches_hud);

	if (m_system->m_debug)
	{
		sf::Text txt_stats;
		txt_stats.setFont(*fnt_small);
		std::string txt = "FPS: " + std::to_string(m_system->getFps()) + "\n " + 
			std::to_string(m_object_manager->getObjects()) + " walls";
		sf::Color col = (m_system->getFps() >= 60 ? sf::Color::Green : sf::Color::Red);
		txt_stats.setString(txt);
		txt_stats.setPosition(16,0);
		txt_stats.setColor(col);
		txt_stats.setCharacterSize(32);

		m_system->m_window->draw(txt_stats);
	}
}

std::string GameState::Next(){
	//std::cout << "Goto MenuState\n--" << std::endl;
	return m_next;
}

bool GameState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}

bool GameState::isPaused()
{
	return m_paused;
}

bool GameState::isBase()
{
	return m_base;
}