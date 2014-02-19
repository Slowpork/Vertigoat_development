// FontManager.h

#pragma once

#include <map>
#include <string>

#include "SFML\Graphics\Font.hpp"

class FontManager
{
public:
	FontManager(const std::string _dir);

	void addFont(const std::string _filename);
	sf::Font* getFont(const std::string _filename);

private:


private:

	std::string m_dir;
	std::map<std::string,sf::Font> m_fonts;
};