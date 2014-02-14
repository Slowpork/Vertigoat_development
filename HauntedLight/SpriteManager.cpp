// SpriteManager.cpp

#include "SpriteManager.h"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"

#include "AnimatedSprite.h"

#include <iostream>

SpriteManager::SpriteManager(std::string _dir)
{
	m_dir = _dir;
}

void SpriteManager::addTexture(const std::string& _filename)
{
	std::string path = m_dir + _filename;
	sf::Texture texture;
	texture.loadFromFile(path);

	std::map<std::string, sf::Texture>::iterator it = m_textures.find(_filename);
	if (it == m_textures.end())
		m_textures.insert( std::pair<std::string, sf::Texture>(_filename, texture));
	else
		std::cout << "  ------------\n ERROR: Texture already exists. \n  -------------";
}

sf::Texture* SpriteManager::getTexture(const std::string& _name)
{
	std::map<std::string,sf::Texture>::iterator it = m_textures.find(_name);
	if (it == m_textures.end())
		return nullptr;
	else
	return &it->second;
}

AnimatedSprite* SpriteManager::addSprite(const std::string& _filename, 
										 int _x, int _y, int _w, int _h, int _frames)
{
	AnimatedSprite* sprite = new AnimatedSprite(_frames, _w, _h);
	
	std::map<std::string, sf::Texture>::iterator it = m_textures.find(_filename);
	if ( it == m_textures.end())
	{
		std::cout << "  ------------\n ERROR: Texture does not exist. \n  -------------";
		return nullptr;
	}

	sprite->setTexture(it->second);
	sprite->setFrame(0);

	return sprite;
}

/*
sf::Sprite* SpriteManager::addSprite(const std::string& _filename, int _x, int _y, int _w, int _h)
{
	sf::Sprite* sprite = new sf::Sprite();

	std::map<std::string, sf::Texture>::iterator it = m_textures.find(_filename);
	if (it == m_textures.end())
	{
		std::cout << "------------\n ERROR: Texture does not exist. \n-------------";
		return nullptr;
	}

	sprite->setTexture(it->second);
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(_x,_y),sf::Vector2i(_w,_h)));

	return sprite;
}*/