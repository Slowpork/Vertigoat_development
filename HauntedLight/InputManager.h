// InputManager.h

#pragma once

//#include "SFML\Window\Keyboard.hpp"
//#include "SFML\Window\Mouse.hpp"
#include "SFML\System\Vector2.hpp"


enum EMouseButton
{
	Left,       ///< The left mouse button
    Right,      ///< The right mouse button
    Middle,     ///< The middle (wheel) mouse button
    XButton1,   ///< The first extra mouse button
    XButton2,   ///< The second extra mouse button

    ButtonCount ///< Keep last -- the total number of mouse buttons
};

/*
namespace sf
{
	class Keyboard;
	class Mouse;
}*/

class KeyboardObject// : public sf::Keyboard
{
	friend class Engine;
public:
	KeyboardObject();

	bool IsDown(int _key) const;
	bool IsDownOnce(int _key) const;
	bool IsDownOnceAny() const;
	
	void PostUpdate();
private:
	bool current[256];
	bool previous[256];
};

class MouseObject// : public sf::Mouse
{
	friend class Engine;
public:
	MouseObject();

	int GetX() const;
	int GetY() const;

	sf::Vector2f getPos() const;
	bool IsDown(EMouseButton _button) const;
	bool IsDownOnce(EMouseButton _button) const;
	bool IsDownOnceAny() const;

	void PostUpdate();

private:
	bool current[ButtonCount];
	bool previous[ButtonCount];

	int x,y;
	sf::Vector2f m_pos;
};