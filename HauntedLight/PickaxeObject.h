//PickaxeObject.h

#pragma once
#include "GameObject.h"



namespace sf
{
	class Sprite;
	class RenderWindow;
};

class PickaxeObject : public GameObject
{
public:
	PickaxeObject(AnimatedSprite* _sprite, Collider* _collider = nullptr);
	~PickaxeObject();

	void Pickup();
	void drawCracks(sf::RenderWindow* _window);
private:

private:

	bool pickedup;
	AnimatedSprite* spr_cracks;
};