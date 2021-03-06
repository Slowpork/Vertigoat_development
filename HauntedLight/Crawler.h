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

	void incSpeed();

	bool needPath();
private:

	void turn();
	void setDir();
	void decideDir();
private:

	// PATHFINDING
	std::vector<sf::Vector2f>* m_path;
	int m_current_node;

	float snap_factor;

	float crawler_speed;

	bool m_turning;
	int m_dir;

	AnimatedSprite* m_spr_idle;
	AnimatedSprite* m_spr_turn;
};