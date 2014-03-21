// PauseState.h

#pragma once
#include "State.h"
#include <string>
#include <SFML\Graphics\Text.hpp>

class System;
class AnimatedSprite;
class Button;
class ObjectManager;

namespace sf
{
	class Font;
}

class PauseState : public State {
public:
	PauseState(System* _system);

	bool Enter();
	void Exit();
	void Pause();
	void Resume();
	bool Update(float _deltatime);
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

	ObjectManager* object_manager;

private: 
	int m_textSize;

	//Buttons
	AnimatedSprite* spr_button_quit;
	Button* m_button_quit;

	AnimatedSprite* spr_button_back;
	Button* m_button_back;

	//Text
	sf::Text m_text_resolution;
	sf::Text m_text_vsync;
	sf::Text m_text_fullscreen;
	sf::Text m_text_volume;
	sf::Font* fnt_options;
};