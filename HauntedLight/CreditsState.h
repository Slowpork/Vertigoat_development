// CreditsState.h

#pragma once
#include "State.h"
#include <string>
#include <SFML\Graphics\Text.hpp>

class System;
class AnimatedSprite;
class Button;

namespace sf
{
class Font;
};

class CreditsState : public State {
public:
	CreditsState(System* _system);

	bool Enter();
	void Exit();
	void Pause();
	void Resume();
	bool Update(float deltatime);
	void Draw();
	std::string Next();
	bool IsType(const std::string &type);
	bool isPaused();
	bool isBase();

private:
	std::string m_name;
	std::string m_next;
	bool m_paused;
	bool m_base;
	System* m_system;

	//STATE SPECIFIC
	int m_textSize_title;
	int m_textSize_name;

	//Buttons
	AnimatedSprite* spr_button_back;
	Button* m_button_back;

	//Font
	sf::Font* fnt_credits;

	//Titles
	sf::Text m_title_leaddesign;
	sf::Text m_title_producer;
	sf::Text m_title_leadprogram;
	sf::Text m_title_leadart;
	sf::Text m_title_sounddesign;
	sf::Text m_title_program;
	sf::Text m_title_art;
	sf::Text m_title_honorable;

	sf::Text m_title_simonjohansson;
	sf::Text m_title_perjohansson;
	sf::Text m_title_carljohansson;
	sf::Text m_title_jonnajarlsson;
	sf::Text m_title_anitastenholm;
	sf::Text m_title_wilhelmjansson;

	//Names
	sf::Text m_name_simonjohansson;
	sf::Text m_name_perjohansson;
	sf::Text m_name_carljohansson;
	sf::Text m_name_jonnajarlsson;
	sf::Text m_name_anitastenholm;
	sf::Text m_name_wilhelmjansson;
};