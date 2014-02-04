/*
//DrawManager.h

#pragma once

#include "Vector2.h"

class Sprite;

class DrawManager
{
	friend class SpriteManager;

public:
	DrawManager();
	~DrawManager();

	bool Initialize(struct SDL_Window* window, int width, int height);
	
	void Cleanup();
	void Clear();
	void Present();
	void Draw(Sprite* sprite, Vector2 position);
	
private:
	struct SDL_Renderer* m_POINTER_renderer;
};
*/