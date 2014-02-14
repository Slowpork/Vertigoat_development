//AnimatedSprite.h

#pragma once
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class Texture;
};

class AnimatedSprite : public sf::Sprite
{
	int m_width, m_height, m_direction;
	float frameCounter, switchFrame, frameSpeed;
	int m_frame;
	int m_amountofFrames;
	int m_startFrame;
	
	AnimatedSprite *m_animSprite;
	sf::Clock clock;
	
public:

	AnimatedSprite();
	AnimatedSprite(int _width, int _height, unsigned int _amountofFrames, AnimatedSprite *_sprite);
	AnimatedSprite(int _width, int _height, int _amountofFrames, sf::Texture &_texture, AnimatedSprite *_sprite);
	AnimatedSprite(sf::Vector2f _dimensions, int _amountofFrames, sf::Texture &_texture, AnimatedSprite *_sprite);

	int getStartFrame();
	void setStartFrame(int _width, int _height, int _frame, unsigned int _amountofFrames);
	void setFrame(int _frame, unsigned int _amountofFrames);
	void playAnimation(int _direction, float _frameDuration, bool _play);
	void playAnimation(float _frameDuration, bool _play, float _deltatime);
};