//OptionsState.cpp

#include "CreditsState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Window\Keyboard.hpp>

#include "System.h"

#include "SpriteManager.h"
#include "InputManager.h"
#include "FontManager.h"

#include "AnimatedSprite.h"
#include "Button.h"

/*

	Sound Bar Dimensions: 456x128px

*/

CreditsState::CreditsState(System* _system)
{
	m_name = "CreditsState";
	m_next = "";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_textSize_title = 28;
	m_textSize_name = 40;

	m_system = _system;
}

bool CreditsState::Enter(){
	std::cout << m_name << std::endl;

	sf::Vector2f scale = m_system->m_scale;

	// Background
	spr_background = m_system->m_sprite_manager->getSprite("Menu/spr_menu_background.png",0,0,1288,720);
	spr_background->setScale(scale.x,scale.y);

	// Title
	spr_title = m_system->m_sprite_manager->getSprite("Menu/spr_title.png",0,0,458,252);
	spr_title->setScale(scale.x,scale.y);
	spr_title->setOrigin(229.f,126);
	spr_title->setPosition(m_system->m_width/2, m_system->m_height/2 - 186.f*scale.y);

	// Candle idle
	spr_candle_idle = m_system->m_sprite_manager->getSprite("Menu/spr_candle_idle.png",0,0,124,124,10);
	spr_candle_idle->setScale(scale.x,scale.y);
	spr_candle_idle->setOrigin(72,72);
	spr_candle_idle->setPosition(m_system->m_width/2 + 6*scale.x, m_system->m_height/2 - 54.f*scale.y + 24*scale.y);

	// Candle
	spr_candle = m_system->m_sprite_manager->getSprite("Menu/spr_candle.png",0,0,410,410);
	spr_candle->setScale(scale.x,scale.y);
	spr_candle->setOrigin(205,205);
	spr_candle->setPosition(m_system->m_width/2, m_system->m_height/2 - 54.f*scale.y);

	fnt_credits = m_system->m_font_manager->getFont("MTCORSVA.TTF");
	
	#pragma region Assign String
	//Titles
	m_title_simonjohansson.setString("Lead designer/Sound designer");
	m_title_perjohansson.setString("Lead programmer");
	m_title_carljohansson.setString("Programmer");
	m_title_jonnajarlsson.setString("Lead artist");
	m_title_anitastenholm.setString("Producer/Artist");
	m_title_wilhelmjansson.setString("Honorable mention");

	//Names
	m_name_anitastenholm.setString("Anita Stenholm");
	m_name_carljohansson.setString("Carl Johansson");
	m_name_jonnajarlsson.setString("Jonna Jarlsson");
	m_name_perjohansson.setString("Per Johansson");
	m_name_simonjohansson.setString("Simon Johansson");
	m_name_wilhelmjansson.setString("Wilhelm Jansson");
	#pragma endregion

	#pragma region Assign Font
	m_name_anitastenholm.setFont(*fnt_credits);
	m_name_carljohansson.setFont(*fnt_credits);
	m_name_jonnajarlsson.setFont(*fnt_credits);
	m_name_perjohansson.setFont(*fnt_credits);
	m_name_simonjohansson.setFont(*fnt_credits);
	m_name_wilhelmjansson.setFont(*fnt_credits);

	m_title_anitastenholm.setFont(*fnt_credits);
	m_title_carljohansson.setFont(*fnt_credits);
	m_title_jonnajarlsson.setFont(*fnt_credits);
	m_title_perjohansson.setFont(*fnt_credits);
	m_title_simonjohansson.setFont(*fnt_credits);
	m_title_wilhelmjansson.setFont(*fnt_credits);
	#pragma endregion

	#pragma region Assign Textsize
	m_name_anitastenholm.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_carljohansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_jonnajarlsson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_perjohansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_simonjohansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_wilhelmjansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));

	m_title_anitastenholm.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_carljohansson.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_jonnajarlsson.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_perjohansson.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_simonjohansson.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_wilhelmjansson.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	#pragma endregion

	#pragma region Assign Text Color
	m_name_anitastenholm.setColor(sf::Color(155,148,129));
	m_name_carljohansson.setColor(sf::Color(155,148,129));
	m_name_jonnajarlsson.setColor(sf::Color(155,148,129));
	m_name_perjohansson.setColor(sf::Color(155,148,129));
	m_name_simonjohansson.setColor(sf::Color(155,148,129));
	m_name_wilhelmjansson.setColor(sf::Color(155,148,129));
	
	m_title_anitastenholm.setColor(sf::Color(155,148,129));
	m_title_carljohansson.setColor(sf::Color(155,148,129));
	m_title_jonnajarlsson.setColor(sf::Color(155,148,129));
	m_title_perjohansson.setColor(sf::Color(155,148,129));
	m_title_simonjohansson.setColor(sf::Color(155,148,129));
	m_title_wilhelmjansson.setColor(sf::Color(155,148,129));
	#pragma endregion

	#pragma region Assign Positions
	m_name_anitastenholm.setPosition(40*scale.x, m_system->m_height - m_name_jonnajarlsson.getGlobalBounds().height -
		m_title_jonnajarlsson.getGlobalBounds().height - 150*scale.y);
	m_name_jonnajarlsson.setPosition(m_name_anitastenholm.getPosition().x, m_name_anitastenholm.getPosition().y +
		m_name_jonnajarlsson.getGlobalBounds().height + m_title_jonnajarlsson.getGlobalBounds().height + 40*scale.y);
	m_name_wilhelmjansson.setPosition(m_system->m_width - m_name_wilhelmjansson.getGlobalBounds().width - 40*scale.x,
		m_name_jonnajarlsson.getPosition().y);
	m_name_simonjohansson.setPosition(m_system->m_width/2 - m_name_simonjohansson.getGlobalBounds().width/2, 
		m_name_anitastenholm.getPosition().y);
	m_name_perjohansson.setPosition(m_name_wilhelmjansson.getPosition().x, m_name_anitastenholm.getPosition().y);
	m_name_carljohansson.setPosition(m_name_simonjohansson.getPosition().x,	m_name_jonnajarlsson.getPosition().y);

	m_title_anitastenholm.setPosition(m_name_anitastenholm.getPosition().x,	m_name_anitastenholm.getPosition().y - 25*scale.y);
	m_title_jonnajarlsson.setPosition(m_name_jonnajarlsson.getPosition().x, m_name_jonnajarlsson.getPosition().y - 25*scale.y);
	m_title_carljohansson.setPosition(m_name_carljohansson.getPosition().x,	m_name_carljohansson.getPosition().y - 25*scale.y);
	m_title_perjohansson.setPosition(m_name_perjohansson.getPosition().x, m_name_perjohansson.getPosition().y - 25*scale.y);
	m_title_simonjohansson.setPosition(m_name_simonjohansson.getPosition().x, m_name_simonjohansson.getPosition().y - 25*scale.y);
	m_title_wilhelmjansson.setPosition(m_name_wilhelmjansson.getPosition().x, m_name_wilhelmjansson.getPosition().y - 25*scale.y);
	#pragma endregion

	return true;
}
void CreditsState::Exit()
{
	std::cout << "  " << m_name << "->";

	delete spr_title;
	spr_title = nullptr;

	delete spr_candle_idle;
	spr_candle_idle = nullptr;

	delete spr_background;
	spr_background = nullptr;

	delete spr_candle;
	spr_candle = nullptr;

	m_paused = false;
}

void CreditsState::Pause()
{
	m_paused = true;
}

void CreditsState::Resume()
{
	m_paused = false;
}

bool CreditsState::Update(float _deltatime){
	//std::cout << "CreditsState::Update" << std::endl;

	if(m_system->m_keyboard->IsDownOnceAny() || m_system->m_mouse->IsDownOnceAny())
	{
		m_next = "";
		return false;
	}
	spr_candle_idle->play(_deltatime);

	return true;
}

void CreditsState::Draw(){
	//std::cout << "CreditsState::Draw" << std::endl;

	//Background
	m_system->m_window->draw(*spr_background);

	//Candle
	m_system->m_window->draw(*spr_candle);
	m_system->m_window->draw(*spr_candle_idle);

	//Names and Roles
	m_system->m_window->draw(m_name_anitastenholm);
	m_system->m_window->draw(m_name_carljohansson);
	m_system->m_window->draw(m_name_jonnajarlsson);
	m_system->m_window->draw(m_name_perjohansson);
	m_system->m_window->draw(m_name_simonjohansson);
	m_system->m_window->draw(m_name_wilhelmjansson);
	m_system->m_window->draw(m_title_anitastenholm);
	m_system->m_window->draw(m_title_carljohansson);
	m_system->m_window->draw(m_title_jonnajarlsson);
	m_system->m_window->draw(m_title_perjohansson);
	m_system->m_window->draw(m_title_simonjohansson);
	m_system->m_window->draw(m_title_wilhelmjansson);

	//Title
	m_system->m_window->draw(*spr_title);
}

std::string CreditsState::Next(){
	//std::cout << "CreditsState::next" << std::endl;
	return m_next;
}

bool CreditsState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}

bool CreditsState::isPaused()
{
	return m_paused;
}

bool CreditsState::isBase()
{
	return m_base;
}