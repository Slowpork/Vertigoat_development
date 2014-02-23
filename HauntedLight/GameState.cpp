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
	std::cout << "  *Created " << m_name << std::endl;

	m_system = _system;
	m_object_manager = new ObjectManager();
}

bool GameState::Enter()
{
	std::cout << m_name << std::endl;

	m_collision_manager = new CollisionManager(m_object_manager);

	m_light_system = new LightSystem(m_system->m_window, m_system->m_view, m_object_manager);

	m_timer = 0.f;

	m_view_beat = Math::PI_HALF;
	m_view_beat = 0.f;

	// PLAYER
	//AnimatedSprite* spr_player = m_system->m_sprite_manager->addSprite(
	//	"player.png",0,0,128,128);

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
	AnimatedSprite* spr_player = m_system->m_sprite_manager->getSprite("spr_player_walk.png",0,0,128,128,8);
	AnimatedSprite* spr_player_run = m_system->m_sprite_manager->getSprite("spr_player_run.png",0,0,132,132,12);
	spr_floor = m_system->m_sprite_manager->getSprite("spr_floor.png",0,0,400,400);

	spr_darkness = m_system->m_sprite_manager->getSprite("darkness.png",0,0,1280,720);
	spr_darkness->setOrigin(1280/2,720/2);
	spr_darkness->setScale((float)m_system->m_width/1280.f,(float)m_system->m_height/720.f);
	spr_darkness->setPosition((float)m_system->m_width/2,(float)m_system->m_height/2);

	
	// WALLS
	const float SIZE = 128;

	bool map[15][25] = 
	{
		{1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	int count = 0;

	for(int Y = 0; Y < 15; Y++)
	{
		for(int X = 0; X < 15; X++)
		{
			if (map[X][Y])
			{
				//addWall(sf::Vector2f(SIZE*X,SIZE*Y));
				count++;
			}
		}
	}

	//std::cout << "  " << count;

	std::cout << "\n";

	Collider* col_player = new Collider(sf::Vector2f(0,0),sf::Vector2f(96,96));

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	player->setPosition(sf::Vector2f(1280/2,720/2));
	player->setSprites(spr_player_run, spr_player_run);

	m_light_system->setBounds(sf::Vector2f(-256,-256),sf::Vector2f(2084,2084));
	m_light_system->update();

	return true;
}

void GameState::Exit(){
	std::cout << "  " << m_name << "->";

	delete player;
	player = nullptr;

	delete m_collision_manager;
	m_collision_manager = nullptr;

	delete m_light_system;
	m_light_system = nullptr;

	m_object_manager->Cleanup();
	delete m_object_manager;
	m_object_manager = nullptr;
}

void GameState::Pause()
{

}

void GameState::Resume()
{

}


void GameState::addWall(sf::Vector2f _pos)
{
	AnimatedSprite* spr_wall = m_system->m_sprite_manager->getSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall* wall = new Wall(spr_wall,col_wall);
	wall->setPosition(_pos);
	m_object_manager->Add(wall,5);
	//m_light_system->addWall(wall.getPosition(),sf::Vector2f(wall.getSprite()->getLocalBounds().width,wall.getSprite()->getLocalBounds().width));
}

void GameState::viewBeat(float _deltatime)
{
	float tracking = player->getSpeed();
	//system("cls");
	//std::cout << "\n  Stamina: " << tracking;

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

	/*
	if (tracking < 100)
	{

		m_view_beat += (_deltatime/10) * (100 - tracking);
		float scaleFactor = .85 + (sin(m_view_beat)+2)*.05;
		m_system->m_view->setSize(sf::Vector2f(m_system->m_width*scaleFactor,m_system->m_height*scaleFactor));
	}
	else if (m_system->m_view->getSize().x < m_system->m_width)
	{
		float scaleValue =_deltatime/10 * 200;
		float ratio = m_system->m_width/m_system->m_height;

		m_system->m_view->setSize(sf::Vector2f(m_system->m_view->getSize().x + scaleValue*ratio,m_system->m_view->getSize().y + scaleValue));
	}
	else
	{
		m_view_beat = Math::PI_HALF;
		m_system->m_view->setSize(sf::Vector2f(m_system->m_width,m_system->m_height));
	}
	//std::cout << "\n  View Width: " <<  m_system->m_view->getSize().x << std::endl;*/

	float scalefactor = 1.f + m_view_beat*.5f;

	m_system->m_view->setSize(sf::Vector2f(m_system->m_width*scalefactor,m_system->m_height*scalefactor));
}

void GameState::FlickerLight(float _deltatime)
{
	m_timer += _deltatime*5;

	if (Random::between(0,10) == 0)
	{
		m_timer = 0.f;
	}

	float factor = abs(sin(m_timer));

	m_light_system->setLightLocation(
		player->getPosition().x - 5.f*factor + 10.f*factor,
		player->getPosition().y - 5.f*factor + 10.f*factor);

	/*
	m_light_system->setLightLocation(
		player->getPosition().x - 5.f*factor + Random::betweenf(0.f,10.f*factor),
		player->getPosition().y - 5.f*factor + Random::betweenf(0.f,10.f*factor));
	*/
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

	viewBeat(_deltatime);

	FlickerLight(_deltatime);
	m_light_system->logic();
	
	// MOVE VIEW
	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);
	
	if (m_system->m_mouse->IsDownOnce(Left))
	{
		snd_thud->play();
		addWall(sf::Vector2f(
			m_system->m_mouse->getPos().x - ((int)m_system->m_mouse->getPos().x % 128),
			m_system->m_mouse->getPos().y - ((int)m_system->m_mouse->getPos().y % 128)));
		m_light_system->update();
	}
	else if (m_system->m_mouse->IsDownOnce(Right))
	{
		int ID = m_object_manager->atPosition(m_system->m_mouse->getPos());
		if ( ID != -1)
		{
			//std::cout << "  at";
			m_object_manager->destroy(ID);
		}
		m_light_system->update();
	}

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Num1))
	{
		m_light_system->setLightBrightness(20);
	}
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Num2))
	{
		m_light_system->setLightBrightness(40);
	}
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Num3))
	{
		m_light_system->setLightBrightness(100);
	}

	if (!m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	return true;
	else
	return false;
}

void GameState::Draw()
{
	// GAME-WORLD #################################
	m_system->m_window->setView(*m_system->m_view);

	// DYNAMIC LIGHTING
	sf::RectangleShape rect_shadow_mask(sf::Vector2f( 
			m_system->m_width*2.f, 
			m_system->m_height*2.f));
	rect_shadow_mask.setFillColor(sf::Color(0,0,0,255));
	rect_shadow_mask.setPosition(m_system->m_view->getCenter().x - m_system->m_view->getSize().x,
					m_system->m_view->getCenter().y - m_system->m_view->getSize().y);

	m_system->m_window->draw(rect_shadow_mask);

	m_light_system->Draw();
	
	// FLOOR
	drawFloor();

	// PLAYER
	m_system->m_window->draw(*player->getSprite());

	// OBJECTS
	m_object_manager->setActiveDepth(5,5);
	m_object_manager->Draw(m_system->m_window);

	// PLAYER COLLISION-BOX
	if (m_system->m_debug)
	{
		m_system->drawDebugRect(player->getPosition(),
			sf::Vector2f(player->getCollider()->m_ext.x,
						player->getCollider()->m_ext.y));
	}

	// INTERFACE ##################################
	m_system->m_window->setView(m_system->m_window->getDefaultView());
	
	// DARKNESS
	m_system->m_window->draw(*spr_darkness);

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