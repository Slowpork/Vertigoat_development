// FontManager.cpp

#include "FontManager.h"

#include <iostream>

FontManager::FontManager(const std::string _dir)
{
	m_dir = _dir;
}

void FontManager::addFont(const std::string _filename)
{
	std::string path = m_dir + _filename;
	sf::Font font;
	font.loadFromFile(path);

	std::map<std::string, sf::Font>::iterator it = m_fonts.find(_filename);
	if (it == m_fonts.end())
		m_fonts.insert( std::pair<std::string, sf::Font>(_filename, font));
	else
		std::cout << "  ------------\n ERROR: Font already exists. \n  -------------";
}

sf::Font* FontManager::getFont(const std::string _filename)
{
	std::map<std::string, sf::Font>::iterator it = m_fonts.find(_filename);
	if ( it == m_fonts.end())
	{
		std::cout << "  ------------\n ERROR: Font does not exist. \n  -------------";
		return nullptr;
	}

	return &it->second;
}