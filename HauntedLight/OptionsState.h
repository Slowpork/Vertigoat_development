//OptionsState.h

#pragma once
#include "State.h"
#include <string>
#include <sstream>
#include <SFML\Graphics\Text.hpp>

class System;
class AnimatedSprite;
class Button;

namespace sf
{
class Font;
}

class OptionsState : public State {
public:
	OptionsState(System* _system);

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
	std::stringstream ss;
	std::string temp;
	bool m_paused;
	bool m_base;
	System* m_system;

	//STATE SPECIFIC

	AnimatedSprite* spr_background;
	AnimatedSprite* spr_volume_bar;
	AnimatedSprite* spr_text_vsync;
	AnimatedSprite* spr_text_fullscreen;
	AnimatedSprite* spr_text_resolution;
	AnimatedSprite* spr_option_resolution;

	//Buttons
	AnimatedSprite* spr_button_volumeup;
	Button* m_button_volumeup;

	AnimatedSprite* spr_button_volumedown;
	Button* m_button_volumedown;
	
	AnimatedSprite* spr_button_apply;
	Button* m_button_apply;

	AnimatedSprite* spr_button_back;
	Button* m_button_back;

	AnimatedSprite* spr_checkbox_empty;
	AnimatedSprite* spr_checkbox_checked;
	Button* m_button_vsync;
	Button* m_button_fullscreen;

	AnimatedSprite* spr_button_resolutionup;
	Button* m_button_resolutionup;

	AnimatedSprite* spr_button_resolutiondown;
	Button* m_button_resolutiondown;

	//Text
	sf::Font* m_font_options;
	sf::Text m_text_resolution;
	sf::Text m_text_vsync;
	sf::Text m_text_fullscreen;
	sf::Text m_text_volume;
	sf::Text m_text_resolution_options;
	sf::Font* fnt_options;

	int m_volbarframe;
	int m_resolution;
	bool m_fullscreen;
	bool m_vsync;
	int m_vol;
	int m_textSize;
};