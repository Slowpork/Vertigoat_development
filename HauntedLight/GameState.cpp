//GameState.cpp

#include "Gamestate.h"
#include "Math.h"

#include <iostream>
#include <string>
#include <time.h>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\View.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\Graphics\CircleShape.hpp"

#include "SFML\Window\Keyboard.hpp"

#include "SFML\System\Vector3.hpp"

#include "SFML\Audio\Listener.hpp"
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
#include "PlayerObject.h"
#include "Crawler.h"
#include "Waller.h"
#include "Critter.h"

#include "AnimatedSprite.h"
#include "Collider.h"

#include <fstream>
#include <sstream>

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
	m_light_updated = false;

	m_object_manager = new ObjectManager();
	m_pickup_manager = new PickupManager();

	m_level_system = new LevelSystem(m_object_manager, m_system->m_sprite_manager);

	m_enemy_manager = new EnemyManager(m_level_system);

	m_collision_manager = new CollisionManager(m_object_manager, m_pickup_manager, m_enemy_manager);

	m_light_system = new LightSystem(m_system->m_window, m_system->m_view, m_object_manager,m_system);

	m_listener = new sf::Listener();
	m_listener->setGlobalVolume(m_system->m_volume*100);

	m_intro = true;
	m_intro_part = 1;

	WIDTH = 0.f;
	HEIGHT = 0.f;

	m_timer = 0.f;
	m_highscore = 0.f;

	m_ui_alpha = 0.f;

	m_view_beat = Math::PI_HALF;
	m_view_beat = 0.f;

	sf::Vector2f scale = m_system->m_scale;

	//Highscore
	m_clock = nullptr;
	m_elapsed_time = 0.0f;
	m_clock = new sf::Clock;

	// SOUNDS
	snd_thud = m_system->m_sound_manager->getSound("thud.wav");
	snd_thud->setVolume(100);

	snd_Equipment_selection = m_system->m_sound_manager->getSound("snd_Equipment_selection.wav");
	snd_pickaxe_pickup		= m_system->m_sound_manager->getSound("snd_pickaxe_pickup.wav");

	snd_Mining_with_pebbles = m_system->m_sound_manager->getSound("snd_Mining_with_pebbles.wav");
	snd_Mining_with_pebbles->setVolume(25.f);
	snd_Mining_Pickaxe = m_system->m_sound_manager->getSound("snd_Mining_Pickaxe.wav");
	snd_Mining_Pickaxe->setVolume(25.f);

	snd_Player_dies = m_system->m_sound_manager->getSound("snd_New_Game_button.wav");
	snd_Player_dies->setVolume(25.f);

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

	spr_cutscene1 = m_system->m_sprite_manager->getSprite("Game/spr_cutscene1.png",0,0,528,192,25);
	spr_cutscene1->setOrigin(264.f,96.f);
	spr_cutscene1->setRotation(-90);
	spr_cutscene1->setScale(.5,.5);

	spr_cutscene2 = m_system->m_sprite_manager->getSprite("Game/spr_cutscene2.png",0,0,528,192,25);
	spr_cutscene2->setOrigin(264.f,96.f);
	spr_cutscene2->setRotation(-90);
	spr_cutscene2->setScale(.5,.5);

	AnimatedSprite* spr_player = m_system->m_sprite_manager->getSprite("Game/spr_player_walk.png",0,0,128,128,8);
	spr_player->setScale(.5,.5);
	AnimatedSprite* spr_player_run = m_system->m_sprite_manager->getSprite("Game/spr_player_run.png",0,0,160,128,6);
	spr_player_run->setScale(.5,.5);
	AnimatedSprite* spr_player_hack = m_system->m_sprite_manager->getSprite("Game/spr_player_hack.png",0,0,148,128,3);
	spr_player_hack->setScale(.5,.5);

	spr_floor = m_system->m_sprite_manager->getSprite("Game/spr_floor.png",0,0,256,256);

	AnimatedSprite* spr_pickaxe = m_system->m_sprite_manager->getSprite("Game/spr_pickaxe_pickup.png",0,0,128,128,8);
	spr_pickaxe->setScale(.5,.5);

	spr_matches_hud = m_system->m_sprite_manager->getSprite("Game/spr_matches_hud.png",0,0,128,128,6);
	spr_matches_hud->setScale(.75f*scale.x,.75f*scale.y);
	spr_matches_hud->setColor(sf::Color(255,255,255,128));
	spr_matches_hud->setPosition((float)m_system->m_width - 128.f*1.5f*scale.x,(float)m_system->m_height - 128.f*scale.y);

	spr_pickaxe_hud = m_system->m_sprite_manager->getSprite("Game/spr_pickaxe_hud.png",0,0,128,128,3);
	spr_pickaxe_hud->setScale(.75f*scale.x,.75f*scale.y);
	spr_pickaxe_hud->setColor(sf::Color(255,255,255,128));
	spr_pickaxe_hud->setPosition((float)m_system->m_width - 128.f*1.5f*scale.x,(float)m_system->m_height - 128.f*scale.y);

	spr_player_shadow = m_system->m_sprite_manager->getSprite("Game/spr_player_shadow.png",0,0,960,1080);
	spr_player_shadow->setOrigin(960.f,540.f);

	spr_darkness = m_system->m_sprite_manager->getSprite("Game/darkness.png",0,0,1280,720);
	spr_darkness->setOrigin(1280/2,720/2);
	spr_darkness->setScale(scale.x,scale.y);
	spr_darkness->setPosition((float)m_system->m_width/2,(float)m_system->m_height/2);

	const float SIZE = 128;

	Collider* col_player = new Collider(sf::Vector2f(0,0),sf::Vector2f(96,96));

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	player->setPosition(sf::Vector2f(256,10*SIZE));
	player->setSprites(spr_player_run, spr_player_run, spr_player_hack);

	addCritter(sf::Vector2f(player->getPosition().x + 256.f,player->getPosition().y));
	
	/*if (!LoadLevel("../data/levels/level1.txt"))
		return false;*/

	m_light_system->logic();
	sf::Vector2f cutscene_pos(player->getPosition().x + 64.f,player->getPosition().y + 64.f);
	spr_cutscene1->setPosition(cutscene_pos);
	spr_cutscene2->setPosition(cutscene_pos);

	sf::Vector2f pos = spr_cutscene2->getPosition();
	player->setPosition(pos);
	
	// WALLS
	
	/*
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
	*/

	//std::cout << "  " << count;

	//std::cout << "\n";
	
	//addPickup(sf::Vector2f(128,128),1);
	//addPickup(sf::Vector2f(256,256),2);

	//m_light_system->setBounds(sf::Vector2f(0,0),sf::Vector2f(3584,3584));
	//m_light_system->setBounds(sf::Vector2f(0,0),sf::Vector2f(WIDTH,HEIGHT));
	

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

	sf::Time elapsed = m_clock->getElapsedTime();
	m_elapsed_time += elapsed.asSeconds();
	std::cout << m_elapsed_time << std::endl;
}

void GameState::Resume()
{
	m_paused = false;
	m_clock->restart();
}

bool GameState::LoadLevel(const std::string _filename)
{
	std::ifstream file;
	file.open(_filename);
	if (!file.is_open())
		return false;

	const float SIZE = 128.f;

	std::string row;
	float X = -SIZE;
	float Y = -SIZE;

	while(!file.eof())
	{
		Y += SIZE;
		X = -SIZE;
		std::getline(file,row,'\n');
		if (row.length() == 0)
			continue;

		for(unsigned int i = 0; i < row.length(); i++)
		{
			X += SIZE;

			bool update = true;

			switch(row[i])
			{
			case 'P': player->setPosition(sf::Vector2f(X ,Y )); break;
			case 'C': addCrawler(sf::Vector2f(X,Y)); break;
			case 'S': addCritter(sf::Vector2f(X,Y)); break;
			case '#': addWall(sf::Vector2f(X,Y),5); break;
			case '@': addWall(sf::Vector2f(X,Y),4); break;
			case 'M': addPickup(sf::Vector2f(X,Y),2); break;
			case 'A': addPickup(sf::Vector2f(X,Y),1); break;
			case 'W': addWaller(sf::Vector2f(X,Y)); break;
			default:
				update = false;
			}

			if (X + 128.f > WIDTH)
				WIDTH = X + 128.f;

			if (Y + 128.f > HEIGHT)
				HEIGHT = Y + 128.f;

		}
	}
}

void GameState::addWall(sf::Vector2f _pos, int _depth)
{
	AnimatedSprite* spr_wall = nullptr;
	if (_depth == 5)
	{
		spr_wall = m_system->m_sprite_manager->getSprite(
			"Game/spr_wall_brick.png",0,0,128,128,16);
	}
	else
	{
		spr_wall = m_system->m_sprite_manager->getSprite(
			"Game/spr_wall_stone.png",0,0,128,128,16);
	}

	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall* wall = new Wall(spr_wall,col_wall);
	wall->setPosition(_pos);

	AnimatedSprite* spr_wall_crack[4];

	for(int i = 0; i < 4; i++)
	{
		spr_wall_crack[i] = m_system->m_sprite_manager->getSprite(
			"Game/spr_crack_overlay.png",0,0,128,128,5);
		spr_wall_crack[i]->setOrigin(64.f,64.f);
		wall->setCracks(spr_wall_crack[i],i);
	}
	
	m_object_manager->Add(wall,_depth);
}

void GameState::addCrawler(sf::Vector2f _pos)
{
	AnimatedSprite* spr_crawler = m_system->m_sprite_manager->getSprite(
		"Game/spr_monster_big.png",0,0,256,256,12);
	AnimatedSprite* spr_crawler_turn = m_system->m_sprite_manager->getSprite(
		"Game/spr_monster_big_turn.png",0,0,128,128,22);

	spr_crawler->setScale(.5f,.5f);
	//spr_crawler_turn->setScale(.5f,.5f);

	spr_crawler->setOrigin(128.f,128.f);
	spr_crawler_turn->setOrigin(64.f,64.f);

	spr_crawler->setRotation(-90.f);

	Collider* col_crawler = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Crawler* crawler = new Crawler(spr_crawler,col_crawler);

	crawler->setSprite(spr_crawler_turn);
	crawler->setPosition(sf::Vector2f(_pos.x + 64.f, _pos.y + 64.f));
	crawler->setDepth(1);
	m_enemy_manager->Add(crawler);
}

void GameState::addCritter(sf::Vector2f _pos)
{
	AnimatedSprite* spr_critter_walk = m_system->m_sprite_manager->getSprite(
		"Game/spr_critter_walk.png",0,0,128,128,7);
	AnimatedSprite* spr_critter_idle = m_system->m_sprite_manager->getSprite(
		"Game/spr_critter_idle.png",0,0,128,128,7);
	AnimatedSprite* spr_critter_attack = m_system->m_sprite_manager->getSprite(
		"Game/spr_critter_attack.png",0,0,128,128,9);

	spr_critter_walk->setOrigin(64.f,64.f);
	spr_critter_idle->setOrigin(64.f,64.f);
	spr_critter_attack->setOrigin(64.f,64.f);

	Collider* col_critter = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Critter* critter = new Critter(spr_critter_idle,col_critter);

	//critter->setSprite(spr_critter_idle,spr_critter_attack);
	critter->addSprite(spr_critter_walk);
	critter->setPosition(_pos);
	critter->setDepth(3);
	m_enemy_manager->Add(critter);
}

void GameState::addWaller(sf::Vector2f _pos)
{
	AnimatedSprite* spr_waller_idle = m_system->m_sprite_manager->getSprite(
		"Game/spr_monster_waller_idle.png",0,0,128,128);
	AnimatedSprite* spr_waller_attack = m_system->m_sprite_manager->getSprite(
		"Game/spr_monster_waller_attack.png",0,0,128,128,10);

	Collider* col_waller = new Collider(sf::Vector2f(0,0), sf::Vector2f(128,128));
	Waller* waller = new Waller(spr_waller_idle, col_waller);
	
	waller->addSprite(spr_waller_attack);
	waller->setPosition(_pos);
	waller->setDepth(2);
	m_enemy_manager->Add(waller);
}

void GameState::addPickup(sf::Vector2f _pos, int _obj)
{
	AnimatedSprite* spr = nullptr;

	if (_obj == 1)
	{
		spr = m_system->m_sprite_manager->getSprite(
		"Game/spr_pickaxe_pickup.png",0,0,128,128);
	}
	else
	{
		spr = m_system->m_sprite_manager->getSprite(
		"Game/spr_matches_pickup.png",0,0,128,128);
	}
	spr->setScale(0.5f,0.5f);
	Collider* col_Pickaxe = new Collider(sf::Vector2f(0,0),sf::Vector2f(64,64));
	GameObject* obj = new GameObject(spr,col_Pickaxe);
	obj->setPosition(sf::Vector2f(_pos.x + 32.f, _pos.y + 32.f));
	obj->setDepth(_obj);
	m_pickup_manager->Add(obj);
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
	return 2.f + sin(m_timer*7.f) + sin(m_timer*3.f) + cos(m_timer*2.f);
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
			//m_system->drawDebugRect(sf::Vector2f(X + 64,Y + 64),sf::Vector2f(128,128));
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

void GameState::pickupCollision()
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
			{
				m_ui_alpha = 128.f;
				m_pickup_manager->destroy(ID);
				snd_pickaxe_pickup->play();
			}
		break;
		case 2:
			if (player->addMatch())
			{
				m_ui_alpha = 128.f;
				m_pickup_manager->destroy(ID);
				snd_Equipment_selection->play();
			}
		break;
		}
	}
}

bool GameState::enemyCollision()
{
	sf::Vector2f offset;
	sf::Vector2f pos;
	int ID, object = -1;
	object = m_collision_manager->checkCollision(player->getCollider(),offset, ENEMY,ID);
	if (object != -1)
	{
		
		GameObject* enemyobject = m_enemy_manager->getObject(ID);
		switch(object)
		{
		case 1:
			pos = enemyobject->getCollider()->m_pos;
			std::cout << "X: " << pos.x << " Y: " << pos.y << std::endl;
			m_crawler_pos = pos;
			return true;
		break;
		case 2:
			if( static_cast<EnemyObject*>(enemyobject)->getSprite()->getFrame() < 7 &&
				static_cast<EnemyObject*>(enemyobject)->getSprite()->getFrame() > 3)
			{
				static_cast<EnemyObject*>(enemyobject)->hasCollided();
				player->blowout();
			}
		break;
		case 3:
			static_cast<EnemyObject*>(enemyobject)->hasCollided();
			//player->blowout();
		break;
		}
		std::cout << object;
	}

	return false;
}

sf::Vector2f GameState::getSide(sf::Vector2f _pos)
{
	sf::Vector2f value(0,0);
	sf::Vector2f p_pos = player->getPosition();

	if (p_pos.x > _pos.x + 128.f)
		value.x = 1;
	if (p_pos.x < _pos.x)
		value.x = -1;

	if (p_pos.y > _pos.y + 128.f)
		value.y = 1;
	if (p_pos.y < _pos.y)
		value.y = -1;

	return value;
}

bool GameState::Update(float _deltatime){
	//std::cout << "GameState::Update" << std::endl;

	sf::Vector2f prev_light_pos = m_light_system->getLightLocation();

	if (m_intro)
	{
		
		player->setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y - _deltatime*16));
		m_system->m_mouse->setPos(m_system->m_width / 2, - 5);
		if (m_intro_part == 1)
		{
			spr_cutscene1->play(_deltatime);
			if (spr_cutscene1->getFrame() >= spr_cutscene1->getFrames() - 1)
				m_intro_part = 2;
		}
		if (m_intro_part == 2)
		{
			spr_cutscene2->play(_deltatime);
			if (spr_cutscene2->getFrame() >= spr_cutscene2->getFrames() - 1)
			{
				sf::Vector2f pos = spr_cutscene2->getPosition();
				player->setPosition(sf::Vector2f(pos.x + 14.f, pos.y));
				m_intro = false;
			}
		}

		m_system->m_view->setCenter(player->getPosition());
		m_system->m_window->setView(*m_system->m_view);

		viewScale(_deltatime);

		//m_level_system->Update(player->getPosition(), player->getPosition());

		FlickerLight(_deltatime);

		m_light_system->logic();

		if (!m_system->m_keyboard->IsDownOnce(sf::Keyboard::Escape))
		return true;
		else
		{
			m_next = "PauseState";
			Pause();
			return false;
		}
	}

	playerCollision();
	pickupCollision();

	if ( enemyCollision() ) // return true if hit Crawler
	{
		//std::cout << "hit!";
<<<<<<< HEAD
		/*
=======
		snd_Player_dies->play();
>>>>>>> 9f975648a85c570a55a604aa27bfd0bfa9e79ec2
		m_highscore = m_elapsed_time;
		m_system->m_highscore = ( m_highscore > m_system->m_highscore ? m_highscore : m_system->m_highscore);
		m_system->writeSettings();
		m_next = "LoseState";
		Pause();
		return false;
		*/
	}

	player->Update(_deltatime);
	m_level_system->Update(player->getPosition(), player->getPosition());
	//m_listener->setPosition(sf::Vector3f(player->getPosition().x,player->getPosition().y,0.f));

	m_enemy_manager->Update(_deltatime, player->getPosition());

	viewScale(_deltatime);

	if (m_ui_alpha > 0.f)
	{
		m_ui_alpha -= _deltatime * 50;
		if (m_ui_alpha < 0.f)
			m_ui_alpha = 0.f;
	}
	
	//Player breathing
	//msc_Player_breathing->setVolume(100 - (player->getStamina()));

	// MOVE VIEW
	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);

	FlickerLight(_deltatime);

	spr_player_shadow->setPosition(player->getPosition());
	spr_player_shadow->turnToPoint(m_light_system->getLightLocation());
	
	if (!m_system->m_keyboard->IsDown(sf::Keyboard::LControl))
	{
		if (m_system->m_mouse->IsDown(Right))
		{
			int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
			if ( ID == -1)
			{
				
				sf::Vector2f pos(floor(m_system->m_mouse->getPos().x - ((int)m_system->m_mouse->getPos().x % 128)),
								floor(m_system->m_mouse->getPos().y - ((int)m_system->m_mouse->getPos().y % 128)));
				addWall(pos, 5);
				m_light_updated = true;
				m_light_system->update();
				m_level_system->pathReset();

				snd_thud->setPosition(m_system->getSoundValue(player->getPosition(),pos));
				snd_thud->play();
			}
		}
		else if (m_system->m_mouse->IsDown(Left)) // HIT WALL
		{
			int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
			if ( ID != -1)
			{
				if (m_object_manager->getDistance(player->getPosition(),ID) < 140.f)
				{
					if (player->doMine(_deltatime))
					{
						m_ui_alpha = 128.f;
						sf::Vector2f side = getSide(m_object_manager->getPosition(ID));
						GameObject* go = m_object_manager->getObject(ID);
						if (go != nullptr)
						{
							if (static_cast<Wall*> (go)->hit(side))
							{
								player->removePickaxe();
								if(player->getPickaxe() == 0)
									snd_thud->play();

								snd_Mining_with_pebbles->play();
								m_object_manager->destroy(ID);
								m_level_system->pathReset();
								m_light_updated = true;
								m_light_system->logic();
							}
							else
								snd_Mining_Pickaxe->play();
						}
					}
				}
			}
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
	}

	sf::Vector2f new_light_pos = m_light_system->getLightLocation();

	if (( prev_light_pos != new_light_pos) && !m_light_updated)
	m_light_system->logic();

	m_light_updated = false;

	if (!m_system->m_keyboard->IsDownOnce(sf::Keyboard::Escape))
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

	m_light_system->Draw();

	// PLAYER SHADOW
	//if (player->hasCandle() )
	{
		//spr_player_shadow->setColor(sf::Color(255,255,255,(int)brightness));
		//std::cout << m_light_system->getLightBrightness() << std::endl;
		//m_system->m_window->draw(*spr_player_shadow);
	}
	
	// FLOOR
	drawFloor();

	// PICKUPS
	m_pickup_manager->Draw(m_system->m_window, brightness);

	// PLAYER
	if (!m_intro)
	{
		player->getSprite()->setColor(sf::Color((int)m_light_system->getLightBrightness()
			,(int)m_light_system->getLightBrightness(),(int)m_light_system->getLightBrightness(),255));
		m_system->m_window->draw(*player->getSprite());
	}
	else
	{
		if (m_intro_part == 1)
		{
			spr_cutscene1->setColor(sf::Color((int)m_light_system->getLightBrightness()
			,(int)m_light_system->getLightBrightness(),(int)m_light_system->getLightBrightness(),255));
			m_system->m_window->draw(*spr_cutscene1);
		}

		if (m_intro_part == 2)
		{
			spr_cutscene2->setColor(sf::Color((int)m_light_system->getLightBrightness()
			,(int)m_light_system->getLightBrightness(),(int)m_light_system->getLightBrightness(),255));
			m_system->m_window->draw(*spr_cutscene2);
		}
	}

	// ENEMIES
	m_enemy_manager->Draw(m_system->m_window);

	// OBJECTS
	m_object_manager->setActiveDepth(4,5);
	m_object_manager->Draw(m_system->m_window, brightness);

	// DEBUG PLAYER COLLISION-BOX
	m_system->drawDebugRect(player->getPosition(),
			sf::Vector2f(player->getCollider()->m_ext.x,
						player->getCollider()->m_ext.y));

	m_system->drawDebugRect(m_light_system->getLightLocation(),
			sf::Vector2f(4,4));

	m_system->drawDebugRect(m_crawler_pos,sf::Vector2f(128.f,128.f));

	// INTERFACE ##################################
	m_system->m_window->setView(m_system->m_window->getDefaultView());
	
	// DARKNESS
	m_system->m_window->draw(*spr_darkness);

	// MATCHES
	if (player->holdMatch())
	{
		spr_matches_hud->setOpacity(m_ui_alpha);
		spr_matches_hud->setFrame(player->getMatches());
		m_system->m_window->draw(*spr_matches_hud);
	}
	else if (player->getPickaxe() > 0)
	{
		spr_pickaxe_hud->setOpacity(m_ui_alpha);
		spr_pickaxe_hud->setFrame(4 - player->getPickaxe());
		m_system->m_window->draw(*spr_pickaxe_hud);
	}

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