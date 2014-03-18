// MenuState.cpp

#include "MenuState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\View.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"

#include "System.h"

#include "SFML\Audio\Sound.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include "SFML\Audio\Music.hpp"

#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "SoundManager.h"

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
	brightness = 0.5f;

	m_system = _system;
}

bool MenuState::Enter()
{
	//std::cout << "Enter " << m_name << std::endl;
	m_paused = false;
	m_base = true;

	state = 0;
	title_alpha = 0.f;
	brightness =  0.5f;

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


	//-------------------------BUTTON-----------------------
	spr_button_play = m_system->m_sprite_manager->getSprite("Menu/spr_button_play.png", 0,0, 219, 64, 2);
	spr_button_play->setScale(scale.x, scale.y);
	m_button_play = new Button(spr_button_play, spr_button_play->getSize().x*spr_button_play->getScale().x,
		spr_button_play->getSize().y*spr_button_play->getScale().y,
		m_system->m_width/2 - (spr_button_play->getSize().x*spr_button_play->getScale().x)/2,
		(m_system->m_height/9)*7 - 32*scale.y);

	spr_button_credits = m_system->m_sprite_manager->getSprite("Menu/spr_button_credits.png", 0,0, 219, 64, 2);
	spr_button_credits->setScale(scale.x, scale.y);
	m_button_credits = new Button(spr_button_credits, spr_button_credits->getSize().x*spr_button_credits->getScale().x,
		spr_button_credits->getSize().y*spr_button_credits->getScale().y,
		m_system->m_width - spr_button_credits->getSize().x*spr_button_credits->getScale().x + 15*scale.x,
		m_system->m_height - spr_button_credits->getSize().y*spr_button_credits->getScale().y - 12*scale.y);

	spr_button_quit = m_system->m_sprite_manager->getSprite("Menu/spr_button_quit.png", 0,0, 219, 64, 2);
	spr_button_quit->setScale(scale.x, scale.y);
	m_button_quit = new Button(spr_button_quit, spr_button_quit->getSize().x*spr_button_quit->getScale().x,
		spr_button_quit->getSize().y*spr_button_quit->getScale().y,
		m_system->m_width/2 + (spr_button_play->getSize().x*spr_button_play->getScale().x)/2,
		(m_system->m_height/9)*7 - 32*scale.y);

	spr_button_options = m_system->m_sprite_manager->getSprite("Menu/spr_button_options.png", 0,0, 219, 64, 2);
	spr_button_options->setScale(scale.x, scale.y);
	m_button_options = new Button(spr_button_options, spr_button_options->getSize().x*spr_button_options->getScale().x,
		spr_button_options->getSize().y*spr_button_options->getScale().y,
		spr_button_play->getPosition().x - spr_button_options->getSize().x*spr_button_options->getScale().x,
		(m_system->m_height/9)*7 - 32*scale.y);
	//---------------------------------------------------------------

	//Sounds
	snd_Start_Up_screen = m_system->m_sound_manager->getSound("snd_Start_Up_screen.wav");
	snd_Start_Up_screen->setVolume(25.f);
	snd_Start_Up_screen->play();
	
	if (snd_Start_Up_screen->getStatus() == snd_Start_Up_screen->Playing)
	{
		music_main = m_system->m_sound_manager->getMusic("msc_Main_Menu.wav");
		music_main->setVolume(25.f);
		music_main->setLoop(true);
		music_main->play();
	}

	snd_Main_Menu_blow_out_candle = m_system->m_sound_manager->getSound("snd_Main_Menu_blow_out_candle.wav");
	snd_Main_Menu_blow_out_candle->setVolume(25.f);

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

	//----------------BUTTON------------
	delete spr_button_play;
	spr_button_play = nullptr;
	delete m_button_play;
	m_button_play = nullptr;

	delete spr_button_credits;
	spr_button_credits = nullptr;
	delete m_button_credits;
	m_button_credits = nullptr;

	delete spr_button_quit;
	spr_button_quit = nullptr;
	delete m_button_quit;
	m_button_quit = nullptr;

	delete spr_button_options;
	spr_button_options = nullptr;
	delete m_button_options;
	m_button_options = nullptr;
	//------------------------------------------

	//Sounds
	music_main->stop();
	snd_Main_Menu_blow_out_candle->stop();
	snd_Start_Up_screen->stop();
	
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
			brightness += _deltatime/2;
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
		
	}

	//-------------------------BUTTON---------------------
	if (m_button_play->Update(_deltatime, m_system->m_mouse))
	{
		snd_Main_Menu_blow_out_candle->play();
		state = 2;
	}
	if(m_button_credits->Update(_deltatime, m_system->m_mouse))
	{
		snd_Main_Menu_blow_out_candle->play();
		m_next = "CreditsState";
		Pause();
		return false;
	}
	if (m_button_options->Update(_deltatime, m_system->m_mouse))
	{
		snd_Main_Menu_blow_out_candle->play();
		m_next = "OptionsState";
		Pause();
		return false;
	}
	if (m_button_quit->Update(_deltatime, m_system->m_mouse))
	{
		snd_Main_Menu_blow_out_candle->play();
		m_next = "";
		return false;
	}
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

	// OPACITY
	float opactiy = title_alpha*255.f;
	spr_title->setOpacity(opactiy);
	m_button_play->getSprite()->setOpacity(opactiy);
	m_button_credits->getSprite()->setOpacity(opactiy);
	m_button_options->getSprite()->setOpacity(opactiy);
	m_button_quit->getSprite()->setOpacity(opactiy);


	m_system->m_window->draw(*spr_title);

	if(!m_paused)
	{
		//------------BUTTON-------------
		m_button_play->Draw(m_system->m_window);
		m_button_credits->Draw(m_system->m_window);
		m_button_options->Draw(m_system->m_window);
		m_button_quit->Draw(m_system->m_window);
		//--------------------------------------
	}

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f( m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,255 - brightness*255));

	m_system->m_window->draw(rect_fade);
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