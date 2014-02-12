//GameState.cpp

//MenuState.cpp

#include "stdafx.h"
#include "Gamestate.h"

GameState::GameState(System* _system){
	m_system = _system;

	m_object_manager = new ObjectManager();

	//light_system = new LightSystem(m_system->m_window);

	sf::Sprite* spr_player = m_system->m_sprite_manager->addSprite(
		"player.png",0,0,128,128);

	spr_cursor = m_system->m_sprite_manager->addSprite(
		"curs.png",0,0,32,32);

	spr_cursor->setOrigin(16,16);

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse, spr_player);
	player->setPosition(sf::Vector2f(1280/2,720/2));

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

	m_object_manager->Draw(m_system->m_window);

	// INTERFACE ##################################
	m_system->m_window->setView(m_system->m_window->getDefaultView());

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