//Crawler.h
#pragma once

#include "EnemyObject.h"
#include <SFML\System\Vector2.hpp>

#include <vector>

namespace sf
{
	class RenderWindow;
};

class Crawler : public EnemyObject
{
public:
	Crawler(AnimatedSprite* _sprite = nullptr, Collider* _col = nullptr);

	void Update(float _deltatime, sf::Vector2f _playerpos);
	void Draw(sf::RenderWindow* _window);

	void setSprite(AnimatedSprite* _sprite);

	void setPath(std::vector<sf::Vector2f>* _path);
private:

	bool turn(int _dir);
private:

	// PATHFINDING
	std::vector<sf::Vector2f>* m_path;
	int m_current_node;

	bool m_turning;

	AnimatedSprite* m_spr_idle;
	AnimatedSprite* m_spr_turn;
};