// InputManager.h

#include "stdafx.h"
#pragma once

enum EMouseButton
{
	Left,       ///< The left mouse button
    Right,      ///< The right mouse button
    Middle,     ///< The middle (wheel) mouse button
    XButton1,   ///< The first extra mouse button
    XButton2,   ///< The second extra mouse button

    ButtonCount ///< Keep last -- the total number of mouse buttons
};

class Keyboard
{
	friend class Engine;
public:
	Keyboard();

	bool IsDown(int _key) const;
	bool IsDownOnce(int _key) const;
	
	void PostUpdate();
private:
	bool current[256];
	bool previous[256];
};

class Mouse
{
	friend class Engine;
public:
	Mouse();

	int GetX() const;
	int GetY() const;
	bool IsDown(EMouseButton _button) const;
	bool IsDownOnce(EMouseButton _button) const;

	void PostUpdate();

private:
	bool current[ButtonCount];
	bool previous[ButtonCount];

	int x,y;
	
};