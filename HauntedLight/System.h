// System.h

#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Window\VideoMode.hpp"

#include <string>

namespace sf
{
	class RenderWindow;
	class View;
	class Clock;
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

	friend class PlayerObject;

public:
	System();
	~System();

	bool Init();
	int getFps();

	void drawDebugRect(sf::Vector2f _pos, sf::Vector2f _size);
	void setDebug(bool _mode);

	void setVideoMode();

private:
	void setFps(int _fps);
	
private:
	// DATA
	int m_height, m_width;
	float m_ticks;
	int m_fps;

	std::string m_title;
	std::vector<sf::VideoMode> m_video_modes;
	bool m_fullscreen;
	bool m_borderless;
	bool m_vsync;

	bool m_debug;

	// SYSTEM PARTS
	sf::RenderWindow* m_window;
	sf::View* m_view;
	sf::Clock* m_clock;

	FileManager* m_file_manager;
	SpriteManager* m_sprite_manager;
	SoundManager* m_sound_manager;
	FontManager* m_font_manager;

	KeyboardObject* m_keyboard;
	MouseObject* m_mouse;
};