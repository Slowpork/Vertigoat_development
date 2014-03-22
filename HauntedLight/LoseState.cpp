// LoseState.cpp

#include "LoseState.h"

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
#include "FontManager.h"

#include "AnimatedSprite.h"
#include "Button.h"

#include "SFML\Window\Keyboard.hpp"

#include "Wall.h"
#include "PlayerObject.h"

#include "Collider.h"

LoseState::LoseState(System* _system)
{
	m_name = "LoseState";
	m_next = "GameState";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_textSize = 28;

	m_system = _system;
	object_manager = new ObjectManager();
}

bool LoseState::Enter(){
	//std::cout << m_name << std::endl;

	sf::Vector2f scale = m_system->m_scale;

	spr_button_back = m_system->m_sprite_manager->getSprite("Menu/spr_button_resume.png",0,0,219,64,2);
	spr_button_back->setScale(scale.x, scale.y);
	m_button_back = new Button(spr_button_back, spr_button_back->getSize().x*spr_button_back->getScale().x, 
		spr_button_back->getSize().y*spr_button_back->getScale().y, 
		m_system->m_width/2 - spr_button_back->getSize().x*spr_button_back->getScale().x,
		(m_system->m_height/12)*7 - 32*scale.y);

	spr_button_quit = m_system->m_sprite_manager->getSprite("Menu/spr_button_quit.png",0,0,219,64,2);
	spr_button_quit->setScale(scale.x, scale.y);
	m_button_quit = new Button(spr_button_quit, spr_button_quit->getSize().x*spr_button_quit->getScale().x, 
		spr_button_quit->getSize().y*spr_button_quit->getScale().y, 
		m_system->m_width/2, (m_system->m_height/12)*7 - 32*scale.y);

	fnt_options = m_system->m_font_manager->getFont("MTCORSVA.TTF");


	m_paused = false;
	return true;
}
void LoseState::Exit(){
	//std::cout << "  " << m_name << "->";

	delete m_button_quit;
	m_button_quit = nullptr;

	delete m_button_back;
	m_button_back = nullptr;

	m_paused = false;
}

void LoseState::Pause()
{
	m_paused = true;
}

void LoseState::Resume()
{
	m_paused = false;
}

bool LoseState::Update(float _deltatime){
	//std::cout << "LoseState::Update" << std::endl;

	if(m_button_back->Update(_deltatime, m_system->m_mouse))
	{
		m_next = "";
		return false;
	}

	if(m_button_quit->Update(_deltatime, m_system->m_mouse))
	{
		m_next = "MenuState";
		return false;
	}
/*
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::P))
	{
		m_next = "";
		return false;
	} else if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
		m_next = "MenuState";
		return false;
	}
*/
	return true;
}
void LoseState::Draw(){
	//std::cout << "LoseState::Draw" << std::endl;

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f( m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));

	m_system->m_window->draw(rect_fade);

	m_button_quit->getSprite()->setOpacity(255);
	m_button_quit->Draw(m_system->m_window);

	m_button_back->getSprite()->setOpacity(255);
	m_button_back->Draw(m_system->m_window);

	object_manager->Draw(m_system->m_window);
}
std::string LoseState::Next(){
	//std::cout << "Goto GameState\n--" << std::endl;
	return m_next;
}
bool LoseState::IsType(const std::string &type){
	return type.compare(m_name) == 0;
}

bool LoseState::isPaused()
{
	return m_paused;
}

bool LoseState::isBase()
{
	return m_base;
}