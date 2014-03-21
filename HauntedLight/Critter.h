//Critter.h
#pragma once

#include "EnemyObject.h"
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RenderWindow;
};

class Critter : public EnemyObject
{
public:
	Critter(AnimatedSprite* _sprite = nullptr, Collider* _col = nullptr);

	void Update(float _deltatime, sf::Vector2f _playerpos);
	void Draw(sf::RenderWindow* _window);

private:
	bool m_chase;
	bool m_home;
	sf::Vector2f m_homePos;
	float m_timer;
	sf::Vector2f m_dir;
};