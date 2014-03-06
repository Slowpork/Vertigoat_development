//MenuState.cpp

#include "MenuState.h"

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

#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Mouse.hpp"

#include "Wall.h"
#include "PlayerObject.h"
#include "AnimatedSprite.h"
#include "Button.h"

#include "Collider.h"

/*

	STATES
	
	0. become lit;
	1. idle
	2. blow

	light
	54px;
	title
	186px;

	9
	32

*/

MenuState::MenuState(System* _system)
{
	m_name = "MenuState";
	m_next = "LoadingState";
	m_paused = false;
	m_base = true;
	std::cout << "  *Created " << m_name << std::endl;

	state = 0;
	title_alpha = 0.f;
	brightness = 0.f;

	m_system = _system;
}

bool MenuState::Enter()
{
	//std::cout << "Enter " << m_name << std::endl;
	m_paused = false;
	m_base = true;

	state = 0;
	title_alpha = 0.f;
	brightness = 0.f;

	object_manager = new ObjectManager();

	sf::Vector2f scale = sf::Vector2f((float)m_system->m_width/1280.f,(float)m_system->m_height/720.f);

	// Background
	spr_background = m_system->m_sprite_manager->getSprite("Menu/spr_menu_background.png",0,0,1288,720);
	spr_background->setScale(scale.x,scale.y);

	// Title
	spr_title = m_system->m_sprite_manager->getSprite("Menu/spr_title.png",0,0,458,252);
	spr_title->setScale(scale.x,scale.y);
	spr_title->setOrigin(229.f,126);
	spr_title->setPosition(m_system->m_width/2, m_system->m_height/2 - 186.f*scale.y);

	// Candle light
	spr_candle_light = m_system->m_sprite_manager->getSprite("Menu/spr_candle_light.png",0,0,124,124,6);
	spr_candle_light->setScale(scale.x,scale.y);
	spr_candle_light->setOrigin(72,72);
	spr_candle_light->setPosition(m_system->m_width/2 + 6*scale.x, m_system->m_height/2 - 54.f*scale.y + 24*scale.y);

	// Candle idle
	spr_candle_idle = m_system->m_sprite_manager->getSprite("Menu/spr_candle_idle.png",0,0,124,124,10);
	spr_candle_idle->setScale(scale.x,scale.y);
	spr_candle_idle->setOrigin(72,72);
	spr_candle_idle->setPosition(m_system->m_width/2 + 6*scale.x, m_system->m_height/2 - 54.f*scale.y + 24*scale.y);

	// Candle blow
	spr_candle_blow = m_system->m_sprite_manager->getSprite("Menu/spr_candle_blow.png",0,0,124,124,5);
	spr_candle_blow->setScale(scale.x,scale.y);
	spr_candle_blow->setOrigin(72,72);
	spr_candle_blow->setPosition(m_system->m_width/2 + 6*scale.x, m_system->m_height/2 - 54.f*scale.y + 24*scale.y);

	// Candle
	spr_candle = m_system->m_sprite_manager->getSprite("Menu/spr_candle.png",0,0,410,410);
	spr_candle->setScale(scale.x,scale.y);
	spr_candle->setOrigin(205,205);
	spr_candle->setPosition(m_system->m_width/2, m_system->m_height/2 - 54.f*scale.y);


	//-------------------------BUTTON------------------------FOR PÄR
	spr_button = m_system->m_sprite_manager->getSprite("Menu/spr_button_play.png", 0,0, 219, 64, 2);
	spr_button->setScale(scale.x, scale.y);
	m_button = new Button(spr_button, spr_button->getSize().x, spr_button->getSize().y, 600, 600);
	//---------------------------------------------------------------

	return true;
}

void MenuState::Exit()
{
	//std::cout << "  " << m_name << "->";

	delete spr_title;
	spr_title = nullptr;

	delete spr_candle_light;
	spr_candle_light = nullptr;

	delete spr_candle_blow;
	spr_candle_blow = nullptr;

	delete spr_candle_idle;
	spr_candle_idle = nullptr;

	delete spr_background;
	spr_background = nullptr;

	delete spr_candle;
	spr_candle = nullptr;

	//----------------BUTTON------------FOR PÄR
	delete spr_button;
	spr_button = nullptr;
	delete m_button;
	m_button = nullptr;
	//------------------------------------------

	m_paused = false;
}

void MenuState::Pause()
{
	m_paused = true;
}

void MenuState::Resume()
{
	m_paused = false;
}

bool MenuState::Update(float _deltatime){
	//std::cout << "MenuState::Update" << std::endl;

	switch(state)
	{
	case 0:
		if (brightness < 1.f)
			brightness += _deltatime;
		else
		{
			brightness = 1.f;
			state++;
			title_alpha = 0.f;
		}

		spr_candle_light->play(_deltatime/2);
		break;
	case 1:
		
		if (title_alpha < 1.f)
			title_alpha += _deltatime/2;

		spr_candle_idle->play(_deltatime);
		break;
	case 2:
		spr_candle_blow->play(_deltatime);

		brightness -= _deltatime*2;
		if (brightness < 0.f)
		{
			m_next = "GameState";
			return false;
		}
		break;
	}

	if (title_alpha > 1.f)
		title_alpha = 1.f;
	if (title_alpha < 0.f)
		title_alpha = 0.f;

	if (brightness > 1.f)
		brightness = 1.f;
	if (brightness < 0.f)
		brightness = 0.f;

	// DEBUG STATES
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Num1))
	{
		state = 0;
		title_alpha = 0.f;
		brightness = 0.f;
		spr_candle_light->setFrame(0);
	}
	else if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Num2))
	{
		brightness = 1.f;
		state = 1;
		spr_candle_idle->setFrame(0);
	}
	else if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Num3))
	{
		brightness = 1.f;
		state = 2;
		spr_candle_blow->setFrame(0);
	}

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
		m_next = "";
		return false;
	}

	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::O))
	{
		m_next = "OptionsState";
		Pause();
		return false;
	}
	
	if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Space))
	{
		state = 2;
	}

	//-------------------------BUTTON--------------------- FOR PÄR
	m_button->Update(_deltatime, m_system->m_mouse);
	//-------------------------------------------------------------

	return true;
}

void MenuState::Draw(){
	//std::cout << "MenuState::Draw" << std::endl;

	m_system->m_window->setView(m_system->m_window->getDefaultView());

	m_system->m_window->draw(*spr_background);

	m_system->m_window->draw(*spr_candle);

	// CANDLE STATE
	switch(state)
	{
	case 0:
		m_system->m_window->draw(*spr_candle_light);
		break;
	case 1:
		m_system->m_window->draw(*spr_candle_idle);
		break;
	case 2:
		m_system->m_window->draw(*spr_candle_blow);
		break;
	}

	// TITLE
	spr_title->setOpacity(title_alpha*255.f);
	m_system->m_window->draw(*spr_title);

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f( m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,255 - brightness*255));

	m_system->m_window->draw(rect_fade);

	//------------BUTTON--------------FOR PÄR
	m_button->Draw(m_system->m_window);
	//---------------------------------------
}

std::string MenuState::Next(){
	//std::cout << "MenuState::next" << std::endl;
	return m_next;
}

bool MenuState::IsType(const std::string &type) {

	//std::cout << "MenuState::IsType" << std::endl;

	return type.compare(m_name) == 0;
}

bool MenuState::isPaused()
{
	return m_paused;
}

bool MenuState::isBase()
{
	return m_base;
}