//GameState.cpp

#include "Gamestate.h"
#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\View.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"

#include "System.h"

#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "InputManager.h"

#include "LightSystem.h"

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
	m_collision_manager = new CollisionManager(m_object_manager);

	m_light_system = new LightSystem(m_system->m_window);

	m_view_beat = Math::PI_HALF;

	// PLAYER
	//AnimatedSprite* spr_player = m_system->m_sprite_manager->addSprite(
	//	"player.png",0,0,128,128);

	AnimatedSprite* spr_player = m_system->m_sprite_manager->addSprite(
		"player_walk.png",0,0,128,128,7);

	Collider* col_player = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));

	spr_floor = m_system->m_sprite_manager->addSprite(
		"floor.png",0,0,400,400);

	// CURSOR
	spr_cursor = m_system->m_sprite_manager->addSprite(
		"curs.png",0,0,16,16);
	spr_cursor->setOrigin(8,8);

	// DARKNESS
	spr_darkness = m_system->m_sprite_manager->addSprite(
		"darkness.png",0,0,1280,720);

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
		{1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
			if (map[X][Y] /*&& count < 25*/)
			{
				addWall(sf::Vector2f(SIZE*X,SIZE*Y));
				count++;
			}
		}
	}

	std::cout << " " << count;

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	player->setPosition(sf::Vector2f(1280/2,720/2));

	m_light_system->setBounds(sf::Vector2f(-256,-256),sf::Vector2f(2084,2084));
	m_light_system->update();

	//sf::Sprite
}

bool GameState::Enter(){
	std::cout << m_name << std::endl;
	return true;
}

void GameState::Exit(){
	std::cout << "  " << m_name << "->";
}

void GameState::addWall(sf::Vector2f _pos)
{
	AnimatedSprite* spr_wall = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall(spr_wall,col_wall);
	wall.setPosition(_pos);
	m_object_manager->Add(wall,5);
	m_light_system->addWall(wall.getPosition(),sf::Vector2f(wall.getSprite()->getLocalBounds().width,wall.getSprite()->getLocalBounds().width));
}

void GameState::viewBeat(float _deltatime)
{
	float tracking = player->getStamina();
	//system("cls");
	//std::cout << "\n  Stamina: " << tracking;
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

	m_system->m_view->setSize(sf::Vector2f(m_system->m_width*1.5,m_system->m_height*1.5));
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
			m_system->m_window->draw(*spr_floor);
		}
	}
}

bool GameState::Update(float _deltatime){
	//std::cout << "GameState::Update" << std::endl;
	
	sf::Vector2f offset;
	if (m_collision_manager->checkCollision(player->getCollider(),offset))
	{
		//std::cout << _deltatime << std::endl;
		player->setPosition(player->getPosition() + offset);
	}

	player->Update(_deltatime);

	spr_cursor->setPosition(m_system->m_mouse->GetX(), m_system->m_mouse->GetY());

	viewBeat(_deltatime);

	m_light_system->setLightLocation(player->getPosition().x,player->getPosition().y);
	m_light_system->logic();
	
	// MOVE VIEW
	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);

	if (m_system->m_mouse->IsDownOnce(Left))
	{
		addWall(sf::Vector2f(
			m_system->m_mouse->getPos().x - ((int)m_system->m_mouse->getPos().x % 128),
			m_system->m_mouse->getPos().y - ((int)m_system->m_mouse->getPos().y % 128)));
		m_light_system->update();
	}
	else if (m_system->m_mouse->IsDownOnce(Right))
	{
		Objects* obj = m_object_manager->atPosition(m_system->m_mouse->getPos());
		if ( obj != nullptr)
		{
			m_object_manager->destroy(obj);
		}
	}

	return true;
}

void GameState::Draw()
{
	// GAME-WORLD #################################
	m_system->m_window->setView(*m_system->m_view);

	// FLOOR
	drawFloor();
	
	// DYNAMIC LIGHTING
	m_light_system->Draw();

	// PLAYER
	m_system->m_window->draw(*player->getSprite());

	m_object_manager->setActiveDepth(5,5);
	m_object_manager->Draw(m_system->m_window);

	// INTERFACE ##################################
	m_system->m_window->setView(m_system->m_window->getDefaultView());
	
	// DARKNESS
	m_system->m_window->draw(*spr_darkness);

	// CURSOR
	m_system->m_window->draw(*spr_cursor);
	
}

std::string GameState::Next(){
	//std::cout << "Goto MenuState\n--" << std::endl;
	return m_next;
}

bool GameState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}