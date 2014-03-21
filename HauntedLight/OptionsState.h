//OptionsState.h

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
	bool m_paused;
	bool m_base;
	bool m_changed;
	bool m_can_inc;
	bool m_can_dec;
	System* m_system;

	//STATE SPECIFIC
	AnimatedSprite* spr_volume_bar;

	//Buttons
	AnimatedSprite* spr_button_volumeup;
	Button* m_button_volumeup;

	AnimatedSprite* spr_button_volumedown;
	Button* m_button_volumedown;
	
	AnimatedSprite* spr_button_apply;
	Button* m_button_apply;

	AnimatedSprite* spr_button_back;
	Button* m_button_back;

	AnimatedSprite* spr_checkbox_empty_fullscreen;
	AnimatedSprite* spr_checkbox_checked_fullscreen;
	Button* m_button_fullscreen;

	AnimatedSprite* spr_checkbox_empty_vsync;
	AnimatedSprite* spr_checkbox_checked_vsync;
	Button* m_button_vsync;

	AnimatedSprite* spr_button_resolutionup;
	Button* m_button_resolutionup;

	AnimatedSprite* spr_button_resolutiondown;
	Button* m_button_resolutiondown;

	//Text
	sf::Text m_text_resolution;
	sf::Text m_text_vsync;
	sf::Text m_text_fullscreen;
	sf::Text m_text_volume;
	sf::Font* fnt_options;

	int m_volbarframe;
	int m_resolution;
	bool m_fullscreen;
	bool m_vsync;
	int m_vol;
	int m_textSize;
};