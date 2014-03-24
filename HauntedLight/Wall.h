// Wall.h

#pragma once
#include "GameObject.h"

namespace sf
{
	class Sprite;
	class RenderWindow;
};

class Wall : public GameObject
{
public:
	Wall(AnimatedSprite* _sprite, Collider* _collider = nullptr);
	~Wall();

	bool hit(sf::Vector2f _side);
	void drawCracks(sf::RenderWindow* _window);
	void setCracks(AnimatedSprite* _sprite, int _index);
private:

private:

	int m_health;
	AnimatedSprite* spr_cracks[4];
};