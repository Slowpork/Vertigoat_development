// SpriteManager.cpp

#include "stdafx.h"
#include "SpriteManager.h"

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
		std::cout << "------------\n ERROR: Texture already exists. \n-------------";
}

sf::Texture* SpriteManager::getTexture(const std::string& _name)
{
	std::map<std::string,sf::Texture>::iterator it = m_textures.find(_name);
	if (it == m_textures.end())
		return nullptr;
	else
	return &it->second;
}

sf::Sprite* SpriteManager::addSprite(const std::string& _filename, int _x, int _y, int _w, int _h)
{
	sf::Sprite* sprite = new sf::Sprite();
	//bool found_prev = false;

	// SEARCH FOR EXISTING TEXTURE
	std::map<std::string, sf::Texture>::iterator it = m_textures.find(_filename);
	if (it == m_textures.end())
	{
		std::cout << "------------\n ERROR: Texture does not exist. \n-------------";
		/*
		std::string path = m_dir + _filename;
		sf::Texture texture;
		texture.loadFromFile(path);
		
		m_textures.insert( std::pair<std::string, sf::Texture>(_filename, texture));
		it = m_textures.find(_filename);
		*/
	}
	else
	{
		// FIND PREVIOUS SPRITE
		/*
		for( auto it_sprites: m_sprites)
		{
			SpriteData temp_data = it_sprites.second;
			if (temp_data.x == _x && temp_data.y == _y && temp_data.w == _w && temp_data.h == _h)
			{
				sprite = it_sprites.second.sprite;
				found_prev = true;
				break;
			}
		}*/
	}

	sprite->setTexture(it->second);
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(_x,_y),sf::Vector2i(_w,_h)));
	/*
	if (!found_prev) // ADD SPRITE DATA
	{
		sprite.setTexture(it->second);
		sprite.setTextureRect(sf::IntRect(sf::Vector2i(_x,_y),sf::Vector2i(_w,_h)));

		SpriteData sprite_data;
		sprite_data.sprite = sprite;
		sprite_data.x = _x;
		sprite_data.y = _y;
		sprite_data.w = _w;
		sprite_data.h = _h;

		m_sprites.insert( std::pair<std::string, SpriteData>(_filename, sprite_data));
	}*/

	return sprite;
}