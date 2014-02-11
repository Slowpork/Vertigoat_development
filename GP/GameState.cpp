//GameState.cpp

//MenuState.cpp

#include "stdafx.h"
#include "Gamestate.h"

GameState::GameState(System* _system){
	m_system = _system;

	object_manager = new ObjectManager();

	/*sf::Sprite* sprite = new sf::Sprite();
	sf::Texture*  tex_player = new sf::Texture();

	tex_player->loadFromFile("../data/sprites/player.png");
	sprite->setTexture(*tex_player);*/

	player = new PlayerObject(m_system->m_keyboard, m_system->m_mouse);
	player->setPosition(sf::Vector2f(1280/2,720/2));

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

	m_system->m_view->setCenter(player->getPosition());
	m_system->m_window->setView(*m_system->m_view);

	return true;
}

void GameState::Draw(){
	//std::cout << "GameState::Draw" << std::endl;

	
	sf::CircleShape shape(10);

	// set the shape color to green
	if (m_system->m_mouse->IsDown(Middle))
		shape.setFillColor(sf::Color::Red);
	else if (m_system->m_mouse->IsDown(Right))
		shape.setFillColor(sf::Color::Blue);
	else
		shape.setFillColor(sf::Color::White);
	shape.setOrigin(10,10);
	//shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(*m_system->m_window).x, sf::Mouse::getPosition(*m_system->m_window).y));
	shape.setPosition(player->getPosition());
	m_system->m_window->draw(shape);

	//m_system->m_window->draw(*player->getSprite());

	//object_manager->Draw(m_system->m_window);
}

std::string GameState::Next(){
	std::cout << "GameState::next" << std::endl;
	return "MenuState";
}

bool GameState::IsType(const std::string &type) {
	return type.compare("GameState") == 0;
}