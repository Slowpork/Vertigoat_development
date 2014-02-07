// Input.cpp

#include "InputManager.h"

Keyboard::Keyboard()
{
	for(int i = 0; i < 256; i++)
	{
		current[i] = false;
		previous[i] = false;
	}
}

bool Keyboard::IsDown(int _key) const
{
	return current[_key];
}

bool Keyboard::IsDownOnce(int _key) const
{
	return current[_key] && !previous[_key];
}

void Keyboard::PostUpdate()
{
	for(int i = 0; i < 256; i++)
	{
		previous[i] = current[i];
	}
}

Mouse::Mouse()
{
	x = 0;
	y = 0;

	for(int i = 0; i < ButtonCount; i++)
	{
		current[i] = false;
		previous[i] = false;
	}
	
}

int Mouse::GetX() const
{
	return x;
}

int Mouse::GetY() const
{
	return y;
}

bool Mouse::IsDown(EMouseButton _button) const
{
	return current[_button];
}

bool Mouse::IsDownOnce(EMouseButton _button) const
{
	return current[_button] && !previous[_button];
}

void Mouse::PostUpdate()
{
	for(int i = 0; i < ButtonCount; i++)
	{
		previous[i] = current[i];
	}
}