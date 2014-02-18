// Input.cpp


#include "InputManager.h"

KeyboardObject::KeyboardObject()
{
	for(int i = 0; i < 256; i++)
	{
		current[i] = false;
		previous[i] = false;
	}
}

bool KeyboardObject::IsDown(int _key) const
{
	return current[_key];
}

bool KeyboardObject::IsDownOnce(int _key) const
{
	return current[_key] && !previous[_key];
}

void KeyboardObject::PostUpdate()
{
	for(int i = 0; i < 256; i++)
	{
		previous[i] = current[i];
	}
}

MouseObject::MouseObject()
{
	x = 0;
	y = 0;

	m_pos = sf::Vector2f(0.f,0.f);

	for(int i = 0; i < ButtonCount; i++)
	{
		current[i] = false;
		previous[i] = false;
	}
}

int MouseObject::GetX() const
{
	return x;
}

int MouseObject::GetY() const
{
	return y;
}

sf::Vector2f MouseObject::getPos() const
{
	return m_pos;
}

bool MouseObject::IsDown(EMouseButton _button) const
{
	return current[_button];
}

bool MouseObject::IsDownOnce(EMouseButton _button) const
{
	return current[_button] && !previous[_button];
}

void MouseObject::PostUpdate()
{
	for(int i = 0; i < ButtonCount; i++)
	{
		previous[i] = current[i];
	}
}