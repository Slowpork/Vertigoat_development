// Wall.h

#pragma once
#include "GameObject.h"

namespace sf
{
	class Sprite;
};

class Wall : public GameObject
{
public:
	Wall(sf::Sprite* _sprite, Collider* _collider = nullptr);
private:

private:
};