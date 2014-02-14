// SpriteManager.h

#pragma once
#include <map>

namespace sf
{
	class Sprite;
	class Texture;
};

class AnimatedSprite;

class SpriteManager
{
public:
	SpriteManager(std::string _dir);

	void addTexture(const std::string& _filename);
	sf::Texture* getTexture(const std::string& _name);

	AnimatedSprite* addSprite(
		const std::string& _filename, int _x, int _y, int _w, int _h, int _frames = 1);

	//sf::Sprite* addSprite(const std::string& _filename, int _x, int _y, int _w, int _h);
	
	void Cleanup();

private:

private:
	std::string m_dir;
	std::map<std::string,sf::Texture> m_textures;
};