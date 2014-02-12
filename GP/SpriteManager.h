// SpriteManager.h

#pragma once
#include "stdafx.h"
//#include "SFML\Graphics\Sprite.hpp"

namespace sf
{
	class Sprite;
	class Texture;
};

class SpriteManager
{
	/*
	struct SpriteData
	{
		int x, y, w, h;
		//sf::Sprite sprite;
	};
	*/
public:
	SpriteManager(std::string _dir);

	sf::Sprite* addSprite(const std::string& _filename, int _x, int _y, int _w, int _h);
	void addTexture(const std::string& _filename);
	sf::Texture* getTexture(const std::string& _name);
	
	void Cleanup();

private:

private:
	std::string m_dir;
	//std::map<std::string,SpriteData> m_sprites;
	std::map<std::string,sf::Texture> m_textures;
};