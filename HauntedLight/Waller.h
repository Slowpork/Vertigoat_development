//Waller.h
#pragma once

#include "EnemyObject.h"
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RenderWindow;
};

class Waller : public EnemyObject
{
public:
	Waller(AnimatedSprite* _sprite = nullptr, Collider* _col = nullptr);

	void Update(float _deltatime, sf::Vector2f _playerpos);
	void Draw(sf::RenderWindow* _window);

	void setSprite(AnimatedSprite* _sprite);

private:
	AnimatedSprite* m_spr_idle,* m_spr_attack;
};