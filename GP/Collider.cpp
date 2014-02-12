// Collider.cpp

#include "stdafx.h"
#include "Collider.h"

Collider::Collider()
	: m_pos(0.0f, 0.0f)
	, m_ext(0.0f,0.0f)
{
}

Collider::Collider(const sf::Vector2f& _pos, const sf::Vector2f& _ext, Type _type)
	: m_pos(_pos)
	, m_ext(_ext)
{
	m_type = _type;
}