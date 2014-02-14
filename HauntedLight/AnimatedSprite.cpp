//AnimatedSprite.cpp

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
	frameCounter = 0;
	switchFrame = 1;
	frameSpeed = 2;

	m_direction = 0;
	m_frame = 0;
	m_startFrame = 0;
}

AnimatedSprite::AnimatedSprite(int _width, int _height, unsigned int _amountofFrames, AnimatedSprite *_sprite)
{
	m_width = _width;
	m_height = _height;
	m_amountofFrames = _amountofFrames;

	m_animSprite = _sprite;
}

AnimatedSprite::AnimatedSprite(int _width, int _height, int _amountofFrames, sf::Texture &_texture, AnimatedSprite *_sprite)
{
	m_amountofFrames = _amountofFrames - 1;
	m_animSprite->setTexture(_texture);
	m_width = _width;
	m_height = _height;

	m_animSprite = _sprite;
}

AnimatedSprite::AnimatedSprite(sf::Vector2f _dimensions, int _amountofFrames, sf::Texture &_texture, AnimatedSprite *_sprite)
{
	m_amountofFrames = _amountofFrames - 1;
	m_animSprite->setTexture(_texture);
	m_width = _dimensions.x;
	m_height = _dimensions.y;

	m_animSprite = _sprite;
}

void AnimatedSprite::setStartFrame(int _width, int _height, int _frame, unsigned int _amountofFrames)
{
	m_amountofFrames = _amountofFrames - 1;
	m_startFrame = _frame;

	m_animSprite->setTextureRect(sf::IntRect(((_frame - 1) * _width), 0, _width, _height));
}

int AnimatedSprite::getStartFrame()
{
	return m_startFrame;
}

//Set the sprite to a specific frame
void AnimatedSprite::setFrame(int _frame, unsigned int _amountofFrames)
{
	m_amountofFrames = _amountofFrames - 1;

	m_animSprite->setTextureRect(sf::IntRect(((_frame - 1) * m_width), 0, m_width, m_height));
}

/*//direction(right = 0, down = 1, left = 2, up = 3), input frame duration in seconds
void AnimatedSprite::playAnimation(int _direction, float _frameDuration, bool play)
{
	if(play == true)
	{
		frameCounter += frameSpeed * m_clock.restart().asSeconds();
		if(frameCounter >= _frameDuration * switchFrame)
		{
			frameCounter = 0;
			m_frame++;
			if(m_frame >= m_width / m_amountofFrames)
			{
				m_frame = 0;
			}
		}
	}else{
		m_frame = 0;
	}

	m_animSprite->setTextureRect(sf::IntRect((m_frame * m_width), 0, m_width, m_height));
	m_animSprite->setOrigin(m_width / 2, m_height / 2);
	//m_animSprite->rotate(_direction * 90);
}*/

void AnimatedSprite::playAnimation(float _frameDuration, bool _play, float _deltatime)
{
	if(_play == true)
	{
		frameCounter += frameSpeed * _deltatime;
		if(frameCounter >= /*_frameDuration */ 0.01f * switchFrame)
		{
			frameCounter = 0;
			m_frame++;
			if(m_frame >= m_amountofFrames)
			{
				m_frame = 0;
			}
		}
	}else{
		m_frame = m_animSprite->getStartFrame();
	}

	m_animSprite->setTextureRect(sf::IntRect((m_frame * m_width), 0, m_width, m_height));
}