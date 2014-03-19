//MatchesObject.h

#pragma once
#include "GameObject.h"



namespace sf
{
	class Sprite;
	class RenderWindow;
};

class MatchesObject : public GameObject
{
public:
	MatchesObject(AnimatedSprite* _sprite, Collider* _collider = nullptr);
	~MatchesObject();

	void Pickup();
	void drawCracks(sf::RenderWindow* _window);
private:

private:
};