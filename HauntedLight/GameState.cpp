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
#include "EnemyManager.h"
#include "PickupManager.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "FontManager.h"

#include "LightSystem.h"
#include "LevelSystem.h"

#include "Random.h"

#include "Wall.h"
#include "PickaxeObject.h"
#include "MatchesObject.h"
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
	critter_spawned = true;

	m_object_manager = new ObjectManager();
	m_pickup_manager = new PickupManager();

	m_enemy_manager = new EnemyManager();

	m_level_system = new LevelSystem(m_object_manager, m_system->m_sprite_manager);

	m_collision_manager = new CollisionManager(m_object_manager, m_pickup_manager);

	m_light_system = new LightSystem(m_system->m_window, m_system->m_view, m_object_manager);

	m_timer = 0.f;

	m_view_beat = Math::PI_HALF;
	m_view_beat = 0.f;

	sf::Vector2f scale = m_system->m_scale;

	// SOUNDS
	snd_thud = m_system->m_sound_manager->getSound("thud.wav");
	snd_thud->setVolume(25.f);

	snd_Mining_with_pebbles = m_system->m_sound_manager->getSound("snd_Mining_with_pebbles.wav");
	snd_Mining_with_pebbles->setVolume(25.f);

	music_main = m_system->m_sound_manager->getMusic("msc_In_Game_Ambient.wav");
	music_main->setVolume(25.f);
	music_main->setLoop(true);
	music_main->play();

	msc_Player_breathing = m_system->m_sound_manager->getMusic("msc_Player_breathing.wav");
	msc_Player_breathing->setVolume(12.f);
	msc_Player_breathing->setLoop(true);
	msc_Player_breathing->play();

	msc_critter_walk = m_system->m_sound_manager->getMusic("msc_critter_walk.wav");
	msc_critter_walk->setVolume(25.f);
	msc_critter_walk->setLoop(true);

	// SPRITES
	AnimatedSprite* spr_player = m_system->m_sprite_manager->getSprite("Game/spr_player_walk.png",0,0,128,128,8);
	spr_player->setScale(.5,.5);
	AnimatedSprite* spr_player_run = m_system->m_sprite_manager->getSprite("Game/spr_player_run.png",0,0,132,132,12);
	spr_player_run->setScale(.5,.5);
	spr_floor = m_system->m_sprite_manager->getSprite("Game/spr_floor.png",0,0,256,256);

	AnimatedSprite* spr_pickaxe = m_system->m_sprite_manager->getSprite("Game/spr_pickaxe_pickup.png",0,0,128,128,8);
	spr_pickaxe->setScale(.5,.5);

	AnimatedSprite* spr_matches = m_system->m_sprite_manager->getSprite("Game/spr_matches_pickup.png",0,0,128,128,8);
	spr_matches->setScale(.5,.5);

	spr_matches_hud = m_system->m_sprite_manager->getSprite("Game/spr_matches_hud.png",0,0,128,128,6);
	spr_matches_hud->setScale(.75f*scale.x,.75f*scale.y);
	spr_matches_hud->setColor(sf::Color(255,255,255,128));
	spr_matches_hud->setPosition((float)m_system->m_width - 128.f*1.5f*scale.x,(float)m_system->m_height - 128.f*scale.y);

	spr_player_shadow = m_system->m_sprite_manager->getSprite("Game/spr_player_shadow.png",0,0,960,1080);
	spr_player_shadow->setOrigin(960.f,540.f);

	spr_critter = m_system->m_sprite_manager->getSprite("Game/spr_critter_walk.png",0,0,128,128,7);
	spr_critter->setPosition(640,640);
	//spr_critter->setRotation(270);

	spr_monster_big = m_system->m_sprite_manager->getSprite("Game/spr_monster_big.png",0,0,256,256,12);
	spr_monster_big->setRotation(-90);

	spr_darkness = m_system->m_sprite_manager->getSprite("Game/darkness.png",0,0,1280,720);
	spr_darkness->setOrigin(1280/2,720/2);
	spr_darkness->setScale(scale.x,scale.y);
	spr_darkness->setPosition((float)m_system->m_width/2,(float)m_system->m_height/2);


	
	// WALLS
	const float SIZE = 128;

	bool map[15][25] = 
	{
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	int count = 0;

	for(int Y = 0; Y < 15; Y++)
	{
		for(int X = 0; X < 25; X++)
		{
			if (map[Y][X])
			{
				//addWall(sf::Vector2f(SIZE*X,SIZE*Y));
				count++;
			}
		}
	}

	//std::cout << "  " << count;

	//std::cout << "\n";

	Collider* col_player = new Collider(sf::Vector2f(0,0),sf::Vector2f(96,96));
	Collider* col_pickaxe = new Collider(sf::Vector2f(0,0),sf::Vector2f(96,96));
	Collider* col_matches = new Collider(sf::Vector2f(0,0),sf::Vector2f(96,96));

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	player->setPosition(sf::Vector2f(256,10*SIZE));
	player->setSprites(spr_player_run, spr_player_run);

	pickaxe = new PickaxeObject(spr_pickaxe, col_pickaxe);
	pickaxe->setPosition(sf::Vector2f(100,100));

	matches = new MatchesObject(spr_matches, col_matches);
	matches->setPosition(sf::Vector2f(100,300));
	


	addPickaxe(sf::Vector2f(SIZE*128,SIZE*128));

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
	delete m_pickup_manager; m_pickup_manager = nullptr;

	//sounds
	music_main->stop();
	msc_Player_breathing->stop();
	snd_thud->stop();
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
		"Game/spr_wall_brick.png",0,0,128,128,16);
	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall* wall = new Wall(spr_wall,col_wall);
	wall->setPosition(_pos);
	m_object_manager->Add(wall,5);
}

void GameState::addPickaxe(sf::Vector2f _pos)
{
	AnimatedSprite* spr_pickaxe = m_system->m_sprite_manager->getSprite(
		"Game/spr_pickaxe_pickup.png",0,0,128,128,16);
<<<<<<< HEAD
	spr_pickaxe->setScale(0.5f,0.5f);
	Collider* col_Pickaxe = new Collider(sf::Vector2f(0,0),sf::Vector2f(64,64));
	PickaxeObject* pickaxe = new PickaxeObject(spr_pickaxe,col_Pickaxe);
=======
	Collider* col_pickaxe = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	PickaxeObject* pickaxe = new PickaxeObject(spr_pickaxe,col_pickaxe);
>>>>>>> f54684f74784a034fab60edadeb383881c21fa27
	pickaxe->setPosition(_pos);
	pickaxe->setDepth(1);
	m_pickup_manager->Add(pickaxe);
}

void GameState::addMatches(sf::Vector2f _pos)
{
	AnimatedSprite* spr_matches = m_system->m_sprite_manager->getSprite(
		"Game/spr_matches_pickup.png",0,0,128,128,16);
	Collider* col_matches = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	MatchesObject* matches = new MatchesObject(spr_matches,col_matches);
	matches->setPosition(_pos);
	m_pickup_manager->Add(matches);
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

float GameState::LightFactor()
{
	return 3.f + sin(m_timer*7.f) + sin(m_timer*3.f) + cos(m_timer*5.f);
}

void GameState::FlickerLight(float _deltatime)
{
	if (player->hasCandle())
	m_timer += _deltatime*5;

	if (Random::between(0,50) == 0)
	{
		//m_timer = 0.f;
	}

	float factor_x = cos(m_timer);
	float factor_y = sin(m_timer);
	float factor_offset = LightFactor()*2;

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
		light_pos.x + player->getPosition().x + factor_offset*factor_x,
		light_pos.y + player->getPosition().y + factor_offset*factor_y);

	/*
	m_light_system->setLightLocation(
		player->getPosition().x - 5.f*factor + 10.f*factor,
		player->getPosition().y - 5.f*factor + 10.f*factor);*/
}

void GameState::drawFloor()
{
	const int floor_size = 256;
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
			m_system->drawDebugRect(sf::Vector2f(X + 64,Y + 64),sf::Vector2f(128,128));
		}
	}
}

void GameState::playerCollision()
{
	sf::Vector2f offset;
	int ID;
	if (m_collision_manager->checkCollision(player->getCollider(),offset, WALLS,ID))
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

void GameState::pickaxeCollision()
{
	sf::Vector2f offset;
	int ID, object = -1;
	object = m_collision_manager->checkCollision(player->getCollider(),offset, PICKUPS,ID);
	if (object != -1)
	{
		//std::cout << "OBJECT: " << object << " ID: " << ID << std::endl;
		switch (object)
		{
		case 1:
			if (player->addPickaxe())
				m_pickup_manager->destroy(ID);
		break;
		case 2:
			if (player->addMatch())
				m_pickup_manager->destroy(ID);
		break;
		}
	}
}

bool GameState::Update(float _deltatime){
	//std::cout << "GameState::Update" << std::endl;

	playerCollision();
	pickaxeCollision();

	player->Update(_deltatime);
	m_level_system->Update(player->getPosition(), player->getPosition());

	//Citter
	spr_critter->play(_deltatime);

	spr_monster_big->play(_deltatime*1.2f);
	spr_monster_big->setPosition(sf::Vector2f(128.f, player->getPosition().y + 512 + 64));

	m_enemy_manager->Update(_deltatime, player->getPosition());

	if (critter_spawned == true)
	{
		msc_critter_walk->play();
		critter_spawned = false;
	}

	viewScale(_deltatime);
	
	//Player breathing
	//msc_Player_breathing->setVolume(100 - (player->getStamina()));

	FlickerLight(_deltatime);
	m_light_system->logic(player->getPosition());
	spr_player_shadow->setPosition(player->getPosition());
	spr_player_shadow->turnToPoint(m_light_system->getLightLocation());
	
	// MOVE VIEW
	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);
	
	if (!m_system->m_keyboard->IsDown(sf::Keyboard::LControl))
	{
		if (m_system->m_mouse->IsDown(Left))
		{
			int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
			if ( ID == -1)
			{
				snd_thud->play();
				addWall(sf::Vector2f(
					floor(m_system->m_mouse->getPos().x - ((int)m_system->m_mouse->getPos().x % 128)),
					floor(m_system->m_mouse->getPos().y - ((int)m_system->m_mouse->getPos().y % 128))
					));
				m_light_system->update();
				m_level_system->pathReset();
			}
		}
		else if (m_system->m_mouse->IsDown(Right)) // HIT WALL
		{
			int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
			if ( ID != -1)
			{
				snd_Mining_with_pebbles->play();
				GameObject* go = m_object_manager->getObject(ID);
				if (go != nullptr)
				{
					//if (static_cast<Wall*> (go)->hit())
					{
						m_object_manager->destroy(ID);
						m_level_system->pathReset();
					}
				}
			}
			m_light_system->update();
		}
	}
	else
	{
		if (m_system->m_mouse->IsDownOnce(Left))
		{
			sf::Vector2f pos(
					floor(player->getPosition().x - ((int)player->getPosition().x % 128)),
					floor(player->getPosition().y - ((int)player->getPosition().y % 128))
					);
			sf::Vector2f dest(
					floor(m_system->m_mouse->getPos().x - ((int)m_system->m_mouse->getPos().x % 128)),
					floor(m_system->m_mouse->getPos().y - ((int)m_system->m_mouse->getPos().y % 128))
					);

			std::vector<sf::Vector2f>* path = m_level_system->getPath(pos,dest);
				if ( path != nullptr)
					player->setPath(path);
		}
		else if (m_system->m_mouse->IsDown(Right)) // HIT WALL
		{
			
		}
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
		//spr_player_shadow->setColor(sf::Color(255,255,255,(int)brightness));
		//std::cout << m_light_system->getLightBrightness() << std::endl;
		//m_system->m_window->draw(*spr_player_shadow);
	}
	
	// FLOOR
	drawFloor();

	// PLAYER
	player->getSprite()->setColor(sf::Color((int)m_light_system->getLightBrightness()
		,(int)m_light_system->getLightBrightness(),(int)m_light_system->getLightBrightness(),255));
	m_system->m_window->draw(*player->getSprite());

<<<<<<< HEAD
	m_enemy_manager->Draw(m_system->m_window);
	
	m_pickup_manager->Draw(m_system->m_window, brightness);
=======
	//Pickups
	m_system->m_window->draw(*pickaxe->getSprite());
	m_system->m_window->draw(*matches->getSprite());

	//Monsters
	m_enemy_manager->Draw(m_system->m_window);
>>>>>>> f54684f74784a034fab60edadeb383881c21fa27

	m_system->m_window->draw(*spr_critter);

	m_system->m_window->draw(*spr_monster_big);

	

	// OBJECTS
	m_object_manager->setActiveDepth(5,5);
	m_object_manager->Draw(m_system->m_window, brightness);

	// DEBUG PLAYER COLLISION-BOX
	m_system->drawDebugRect(player->getPosition(),
			sf::Vector2f(player->getCollider()->m_ext.x,
						player->getCollider()->m_ext.y));

	m_system->drawDebugRect(m_light_system->getLightLocation(),
			sf::Vector2f(4,4));

	// INTERFACE ##################################
	m_system->m_window->setView(m_system->m_window->getDefaultView());
	
	// DARKNESS
	m_system->m_window->draw(*spr_darkness);

	// MATCHES
	spr_matches_hud->setFrame(player->getMatches());
	m_system->m_window->draw(*spr_matches_hud);

	// DEBUG WALLS
	std::string txt = std::to_string(m_object_manager->getObjects()) + " walls";
	m_system->drawDebugText(sf::Vector2f(16,32),txt);
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