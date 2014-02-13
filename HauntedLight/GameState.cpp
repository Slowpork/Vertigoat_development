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

#include "Collider.h"

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
	sf::Sprite* spr_player = m_system->m_sprite_manager->addSprite(
		"player.png",0,0,128,128);
	Collider* col_player = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));

	// CURSOR
	spr_cursor = m_system->m_sprite_manager->addSprite(
		"curs.png",0,0,16,16);
	spr_cursor->setOrigin(8,8);

	// DARKNESS
	spr_darkness = m_system->m_sprite_manager->addSprite(
		"darkness.png",0,0,1280,720);

	// WALLS
	sf::Sprite* spr_wall = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall(spr_wall,col_wall);
	wall.setPosition(sf::Vector2f(0,0));
	m_object_manager->Add(wall,5);
	m_light_system->addWall(wall.getPosition(),sf::Vector2f(wall.getSprite()->getLocalBounds().width,wall.getSprite()->getLocalBounds().width));

	sf::Sprite* spr_wall1 = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall1 = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall1(spr_wall1,col_wall1);
	wall1.setPosition(sf::Vector2f(128,0));
	m_object_manager->Add(wall1,5);
	m_light_system->addWall(wall1.getPosition(),sf::Vector2f(wall1.getSprite()->getLocalBounds().width,wall1.getSprite()->getLocalBounds().width));
	
	sf::Sprite* spr_wall2 = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall2 = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall2(spr_wall2,col_wall2);
	wall2.setPosition(sf::Vector2f(512,-128));
	m_object_manager->Add(wall2,5);
	m_light_system->addWall(wall2.getPosition(),sf::Vector2f(wall2.getSprite()->getLocalBounds().width,wall2.getSprite()->getLocalBounds().width));

	sf::Sprite* spr_wall3 = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall3 = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall3(spr_wall3,col_wall3);
	wall3.setPosition(sf::Vector2f(512,0));
	m_object_manager->Add(wall3,5);
	m_light_system->addWall(wall3.getPosition(),sf::Vector2f(wall3.getSprite()->getLocalBounds().width,wall3.getSprite()->getLocalBounds().width));

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	//player->setPosition(sf::Vector2f(1280/2,720/2));

	m_light_system->loadMap(sf::Vector2f(-256,-256),sf::Vector2f(2084,2084));

	//sf::Sprite
}

bool GameState::Enter(){
	std::cout << m_name << std::endl;
	return true;
}

void GameState::Exit(){
	std::cout << "  " << m_name << "->";
}

void GameState::viewBeat(float _deltatime)
{
	float tracking = player->getStamina();
	//system("cls");
	//std::cout << "\n  Stamina: " << tracking;
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
	//std::cout << "\n  View Width: " <<  m_system->m_view->getSize().x << std::endl;

	//m_system->m_view->setSize(sf::Vector2f(m_system->m_view->getSize().x*2,m_system->m_view->getSize().y*2));
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

	return true;
}

void GameState::Draw()
{
	// GAME-WORLD #################################
	m_system->m_window->setView(*m_system->m_view);
	
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