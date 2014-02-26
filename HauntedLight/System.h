// System.h

#pragma once
#include "SFML\System\Vector2.hpp"

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
public:
	System();
	~System();

	bool Init();
	int getFps();

	void drawDebugRect(sf::Vector2f _pos, sf::Vector2f _size);
	void setDebug(bool _mode);

private:
	void setFps(int _fps);
	
private:

	int m_height, m_width;
	float m_ticks;
	int m_fps;

	bool m_fullscreen;
	bool m_debug;

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