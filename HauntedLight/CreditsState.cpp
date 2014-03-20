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

	m_textSize_title = 32;
	m_textSize_name = 40;

	m_system = _system;
}

bool CreditsState::Enter(){
	std::cout << m_name << std::endl;

	sf::Vector2f scale = m_system->m_scale;

	
	#pragma region Assign String
	//Titles
	m_title_art.setString("Artist");
	m_title_honorable.setString("Honorable mention");
	m_title_leadart.setString("Lead Artist");
	m_title_leaddesign.setString("Lead Designer");
	m_title_leadprogram.setString("Lead Programmer");
	m_title_producer.setString("Producer");
	m_title_program.setString("Progammer");
	m_title_sounddesign.setString("Sound Designer");

	//Names
	m_name_anitastenholm.setString("Anita Stenholm");
	m_name_carljohansson.setString("Carl Johansson");
	m_name_jonnajarlsson.setString("Jonna Jarlsson");
	m_name_perjohansson.setString("Per Johansson");
	m_name_simonjohansson.setString("Simon Johansson");
	m_name_wilhelmjansson.setString("Wilhelm Jansson");
	#pragma endregion

	#pragma region Assign Font
	m_title_art.setFont(*fnt_credits);
	m_title_honorable.setFont(*fnt_credits);
	m_title_leadart.setFont(*fnt_credits);
	m_title_leaddesign.setFont(*fnt_credits);
	m_title_leadprogram.setFont(*fnt_credits);
	m_title_producer.setFont(*fnt_credits);
	m_title_program.setFont(*fnt_credits);
	m_title_sounddesign.setFont(*fnt_credits);
	m_name_anitastenholm.setFont(*fnt_credits);
	m_name_carljohansson.setFont(*fnt_credits);
	m_name_jonnajarlsson.setFont(*fnt_credits);
	m_name_perjohansson.setFont(*fnt_credits);
	m_name_simonjohansson.setFont(*fnt_credits);
	m_name_wilhelmjansson.setFont(*fnt_credits);
	#pragma endregion

	#pragma region Assign Textsize
	m_title_art.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_honorable.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_leadart.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_leaddesign.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_leadprogram.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_producer.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_program.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_title_sounddesign.setCharacterSize((int)(m_textSize_title*((scale.x + scale.y)/2)));
	m_name_anitastenholm.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_carljohansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_jonnajarlsson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_perjohansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_simonjohansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	m_name_wilhelmjansson.setCharacterSize((int)(m_textSize_name*((scale.x + scale.y)/2)));
	#pragma endregion

	#pragma region Assign Text Color
	m_title_art.setColor(sf::Color(155,148,129));
	m_title_honorable.setColor(sf::Color(155,148,129));
	m_title_leadart.setColor(sf::Color(155,148,129));
	m_title_leaddesign.setColor(sf::Color(155,148,129));
	m_title_leadprogram.setColor(sf::Color(155,148,129));
	m_title_producer.setColor(sf::Color(155,148,129));
	m_title_program.setColor(sf::Color(155,148,129));
	m_title_sounddesign.setColor(sf::Color(155,148,129));
	m_name_anitastenholm.setColor(sf::Color(155,148,129));
	m_name_carljohansson.setColor(sf::Color(155,148,129));
	m_name_jonnajarlsson.setColor(sf::Color(155,148,129));
	m_name_perjohansson.setColor(sf::Color(155,148,129));
	m_name_simonjohansson.setColor(sf::Color(155,148,129));
	m_name_wilhelmjansson.setColor(sf::Color(155,148,129));
	#pragma endregion

	#pragma region Assign Positions
	m_title_art.setPosition(m_system->m_width/2 - m_title_art.getGlobalBounds().width/2, 0);
	m_title_honorable.setPosition(m_system->m_width/2 - m_title_honorable.getGlobalBounds().width, 0);
	m_title_leadart.setPosition(m_system->m_width/2 - m_title_leadart.getGlobalBounds().width, 0);
	m_title_leaddesign.setPosition(m_system->m_width/2 - m_title_leaddesign.getGlobalBounds().width, 0);
	m_title_leadprogram.setPosition(m_system->m_width/2 - m_title_leadprogram.getGlobalBounds().width, 0);
	m_title_producer.setPosition(m_system->m_width/2 - m_title_producer.getGlobalBounds().width, 0);
	m_title_program.setPosition(m_system->m_width/2 - m_title_program.getGlobalBounds().width, 0);
	m_title_sounddesign.setPosition(m_system->m_width/2 - m_title_sounddesign.getGlobalBounds().width, 0);
	m_name_anitastenholm.setPosition(m_system->m_width/2 - m_name_anitastenholm.getGlobalBounds().width, 0);
	m_name_carljohansson.setPosition(m_system->m_width/2 - m_name_carljohansson.getGlobalBounds().width, 0);
	m_name_jonnajarlsson.setPosition(m_system->m_width/2 - m_name_jonnajarlsson.getGlobalBounds().width, 0);
	m_name_perjohansson.setPosition(m_system->m_width/2 - m_name_perjohansson.getGlobalBounds().width, 0);
	m_name_simonjohansson.setPosition(m_system->m_width/2 - m_name_simonjohansson.getGlobalBounds().width, 0);
	m_name_wilhelmjansson.setPosition(m_system->m_width/2 - m_name_wilhelmjansson.getGlobalBounds().width, 0);
	#pragma endregion

	return true;
}
void CreditsState::Exit()
{
	std::cout << "  " << m_name << "->";

	delete m_button_back;
	m_button_back = nullptr;

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
	
	if(m_system->m_keyboard->IsDownOnce(sf::Keyboard::C))
	{
		m_next = "";
		return false;
	}

	return true;
}

void CreditsState::Draw(){
	//std::cout << "CreditsState::Draw" << std::endl;

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f(m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));

	//m_system->m_window->draw(rect_fade);

	m_system->m_window->draw(m_title_art);
	m_system->m_window->draw(m_title_honorable);
	m_system->m_window->draw(m_title_leadart);
	m_system->m_window->draw(m_title_leaddesign);
	m_system->m_window->draw(m_title_leadprogram);
	m_system->m_window->draw(m_title_producer);
	m_system->m_window->draw(m_title_program);
	m_system->m_window->draw(m_title_sounddesign);
	m_system->m_window->draw(m_name_anitastenholm);
	m_system->m_window->draw(m_name_carljohansson);
	m_system->m_window->draw(m_name_jonnajarlsson);
	m_system->m_window->draw(m_name_perjohansson);
	m_system->m_window->draw(m_name_simonjohansson);
	m_system->m_window->draw(m_name_wilhelmjansson);
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