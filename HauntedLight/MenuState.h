// MenuState.h

#pragma once
#include "State.h"
#include <string>

class System;
class ObjectManager;
class AnimatedSprite;
class Button;
class MouseObject;

namespace sf
{
	class Sound;
	class Music;
	class Font;
};

class MenuState : public State
{
public:
	MenuState(System* _system);

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
	
	// STATE SPECIFIC

	AnimatedSprite* spr_background;
	AnimatedSprite* spr_title;
	AnimatedSprite* spr_candle_light;
	AnimatedSprite* spr_candle_blow;
	AnimatedSprite* spr_candle_idle;
	AnimatedSprite* spr_candle;

	//--------------BUTTON---------------
	AnimatedSprite* spr_button_play;
	AnimatedSprite* spr_button_credits;
	AnimatedSprite* spr_button_quit;
	AnimatedSprite* spr_button_options;

	Button* m_button_play;
	Button* m_button_credits;
	Button* m_button_quit;
	Button* m_button_options;
	//-------------------------------------------

	//Sounds
	sf::Sound* snd_Start_Up_screen;
	sf::Sound* snd_Main_Menu_blow_out_candle;
	sf::Sound* snd_New_Game_button;
	sf::Music* music_main;

	int state;
	float brightness;
	float title_alpha;
};