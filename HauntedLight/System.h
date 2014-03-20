// System.h

#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Vector3.hpp"
#include "SFML\Window\VideoMode.hpp"
#include "SFML\Graphics\Color.hpp"


#include <string>

namespace sf
{
	class RenderWindow;
	class View;
	class Clock;
	class Image;
	class Font;
};

class SpriteManager;
class KeyboardObject;
class MouseObject;
class FileManager;
class SoundManager;
class FontManager;

class System
{
	friend class Engine;
	friend class State;

	friend class GameState;
	friend class LoadingState;
	friend class PauseState;
	friend class MenuState;
	friend class OptionsState;
	friend class CreditsState;

	friend class PlayerObject;

public:
	System();
	~System();

	bool Init();
	int getFps();

	void drawDebugRect(sf::Vector2f _pos, sf::Vector2f _size);
	void drawDebugText(sf::Vector2f _pos, std::string _value, sf::Color _color = sf::Color::Green);

	sf::Vector3f getSoundValue(sf::Vector2f _playerpos, sf::Vector2f _source);

	void toggleDebug();

	void setVideoMode();

	float getVolume();
	void setVolume(float _newvolume);

private:
	void setFps(int _fps);
	void ProcessLoad();
	
private:
	// LOADING
	int m_load_parts;
	int m_load_current;

	// DATA
	int m_height, m_width, m_bit;
	sf::Vector2f m_scale;
	float m_ticks;
	int m_fps;

	std::string m_title;
	std::vector<sf::VideoMode> m_video_modes;
	bool m_fullscreen;
	bool m_borderless;
	bool m_vsync;

	sf::Font* fnt_debug;
	bool m_debug;

	// SOUND
	float m_volume;

	// SYSTEM PARTS
	sf::RenderWindow* m_window;
	sf::Image* m_icon;
	sf::View* m_view;
	sf::Clock* m_clock;

	FileManager* m_file_manager;
	SpriteManager* m_sprite_manager;
	SoundManager* m_sound_manager;
	FontManager* m_font_manager;

	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;
};