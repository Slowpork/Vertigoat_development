// Collider.h

#pragma once

#include "SFML/System/Vector2.hpp"

enum Type
{
	Rect,
	Circle
};

class Collider
{
public:
	Collider();
	Collider(const sf::Vector2f& _pos, const sf::Vector2f& _ext, Type _type = Rect);
	~Collider(){};

	//bool Overlap(Collider& _other, sf::Vector2f&_offset);

	sf::Vector2f m_pos;
	sf::Vector2f m_ext;
	int m_type;
};