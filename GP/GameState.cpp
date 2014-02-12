//GameState.cpp

//MenuState.cpp

#include "stdafx.h"
#include "Gamestate.h"

GameState::GameState(System* _system){
	m_system = _system;

	m_object_manager = new ObjectManager();
	m_collision_manager = new CollisionManager(m_object_manager);

	//light_system = new LightSystem(m_system->m_window);

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

	sf::Sprite* spr_wall1 = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall1 = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall1(spr_wall1,col_wall1);
	wall1.setPosition(sf::Vector2f(128,0));
	m_object_manager->Add(wall1,5);

	sf::Sprite* spr_wall2 = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall2 = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall2(spr_wall2,col_wall2);
	wall2.setPosition(sf::Vector2f(256,0));
	m_object_manager->Add(wall2,5);

	sf::Sprite* spr_wall3 = m_system->m_sprite_manager->addSprite(
		"wall.png",0,0,128,128);
	Collider* col_wall3 = new Collider(sf::Vector2f(0,0),sf::Vector2f(128,128));
	Wall wall3(spr_wall3,col_wall3);
	wall3.setPosition(sf::Vector2f(512,0));
	m_object_manager->Add(wall3,5);
	

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player, col_player);
	//player->setPosition(sf::Vector2f(1280/2,720/2));

	//sf::Sprite

	std::cout << "GameState::GameState" << std::endl;
}

bool GameState::Enter(){
	std::cout << "GameState::Enter" << std::endl;

	return true;
}

void GameState::Exit(){
	std::cout << "GameState::Exit" << std::endl;
}

bool GameState::Update(float _deltatime){
	//std::cout << "GameState::Update" << std::endl;
	
	sf::Vector2f offset;
	if (m_collision_manager->checkCollision(player->getCollider(),offset))
		std::cout << _deltatime << std::endl;

	player->Update(_deltatime);

	spr_cursor->setPosition(m_system->m_mouse->GetX(), m_system->m_mouse->GetY());

	return true;
}

void GameState::Draw(){
	//std::cout << "GameState::Draw" << std::endl;

	// MOVE VIEW
	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);

	// GAME-WORLD #################################
	m_system->m_window->setView(*m_system->m_view);

	// PLAYER
	m_system->m_window->draw(*player->getSprite());

	sf::RectangleShape shape;
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(2);
	shape.setSize(sf::Vector2f(128,128));
	shape.setFillColor(sf::Color(0,0,0,0));

	shape.setPosition(player->getCollider()->m_pos);

	m_system->m_window->draw(shape);

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
	std::cout << "GameState::next" << std::endl;
	return "MenuState";
}

bool GameState::IsType(const std::string &type) {
	return type.compare("GameState") == 0;
}