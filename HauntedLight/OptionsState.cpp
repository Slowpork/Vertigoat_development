//OptionsState.cpp

#include "OptionsState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"

#include "System.h"

#include "ObjectManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "FontManager.h"

#include "AnimatedSprite.h"
#include "Button.h"

/*

	Sound Bar Dimensions: 456x128px

*/

OptionsState::OptionsState(System* _system)
{
	m_name = "OptionsState";
	m_next = "";
	m_paused = false;
	m_base = false;
	std::cout << "  *Created " << m_name << std::endl;

	m_resolution = 0;

	m_system = _system;
}

bool OptionsState::Enter(){
	std::cout << m_name << std::endl;

	object_manager = new ObjectManager();

	sf::Vector2f scale = m_system->m_scale;

	spr_button_resolutiondown = m_system->m_sprite_manager->getSprite("Options/spr_button_resolution_low.png",0,0,128,128,2);
	spr_button_resolutiondown->setScale(0.5*scale.x, 0.5*scale.y);
	m_button_resolutiondown = new Button(spr_button_resolutiondown, spr_button_resolutiondown->getSize().x*spr_button_resolutiondown->getScale().x,
		spr_button_resolutiondown->getSize().y*spr_button_resolutiondown->getScale().y,
		m_system->m_width/2 - 250 * scale.x, m_system->m_height/2 - 250 * scale.y);

	spr_button_resolutionup = m_system->m_sprite_manager->getSprite("Options/spr_button_resolution_high.png",0,0,128,128,2);
	spr_button_resolutionup->setScale(0.5*scale.x,0.5*scale.y);
	m_button_resolutionup = new Button(spr_button_resolutionup, spr_button_resolutionup->getSize().x*spr_button_resolutionup->getScale().x,
		spr_button_resolutionup->getSize().y*spr_button_resolutionup->getScale().y,
		m_system->m_width/2 + 186 * scale.x, m_system->m_height/2 - 250 * scale.y);

	spr_volume_bar = m_system->m_sprite_manager->getSprite("Options/spr_volume_bars.png",0,0,456,128,10);
	spr_volume_bar->setScale(scale.x, 0.5*scale.y);
	spr_volume_bar->setPosition((m_system->m_width/2 - (spr_volume_bar->getSize().x*spr_volume_bar->getScale().x)/2),
		m_system->m_height/2);

	spr_button_volumedown = m_system->m_sprite_manager->getSprite("Options/spr_volume_low.png",0,0,128,128,2);
	spr_button_volumedown->setScale(0.5*scale.x, 0.5*scale.y);
	m_button_volumedown = new Button(spr_button_volumedown, spr_button_volumedown->getSize().x*spr_button_volumedown->getScale().x,
		spr_button_volumedown->getSize().y*spr_button_volumedown->getScale().y,
		(spr_volume_bar->getPosition().x - (spr_button_volumedown->getSize().x*spr_button_volumedown->getScale().x) - 20),
		spr_volume_bar->getPosition().y);

	spr_button_volumeup = m_system->m_sprite_manager->getSprite("Options/spr_volume_high.png",0,0,128,128,2);
	spr_button_volumeup->setScale(0.5*scale.x, 0.5*scale.y);
	m_button_volumeup = new Button(spr_button_volumeup, spr_button_volumeup->getSize().x*spr_button_volumeup->getScale().x,
		spr_button_volumeup->getSize().y*spr_button_volumeup->getScale().y,
		(spr_volume_bar->getPosition().x + spr_volume_bar->getSize().x*spr_volume_bar->getScale().x + 20),
		spr_volume_bar->getPosition().y);

	spr_checkbox_fullscreen = m_system->m_sprite_manager->getSprite("Options/spr_checkbox.png",0,0,128,128,2);
	spr_checkbox_fullscreen->setScale(0.5*scale.x, 0.5*scale.y);
	m_button_fullscreen = new Button(spr_checkbox_fullscreen, spr_checkbox_fullscreen->getSize().x*spr_checkbox_fullscreen->getScale().x,
		spr_checkbox_fullscreen->getSize().y*spr_checkbox_fullscreen->getScale().y, 
		m_system->m_width/2 + 150*scale.x, m_system->m_height/2 - 150*scale.y);

	spr_checkbox_vsync = m_system->m_sprite_manager->getSprite("Options/spr_checkbox.png",0,0,128,128,2);
	spr_checkbox_vsync->setScale(0.5*scale.x, 0.5*scale.y);
	m_button_vsync = new Button(spr_checkbox_vsync, spr_checkbox_vsync->getSize().x*spr_checkbox_vsync->getScale().x,
		spr_checkbox_vsync->getSize().y*spr_checkbox_vsync->getScale().y, 
		m_system->m_width/2 - 214*scale.x, m_system->m_height/2 - 150*scale.y);

	spr_button_back = m_system->m_sprite_manager->getSprite("Options/spr_button_return.png",0,0,219,64,2);
	spr_button_back->setScale(scale.x, scale.y);
	m_button_back = new Button(spr_button_back, spr_button_back->getSize().x*spr_button_back->getScale().x, 
		spr_button_back->getSize().y*spr_button_back->getScale().y, 
		m_system->m_width/2, (m_system->m_height/9)*7 - 32*scale.y);

	spr_button_apply = m_system->m_sprite_manager->getSprite("Options/spr_button_apply.png",0,0,219,64,2);
	spr_button_apply->setScale(scale.x, scale.y);
	m_button_apply = new Button(spr_button_apply, spr_button_apply->getSize().x*spr_button_apply->getScale().x, 
		spr_button_apply->getSize().y*spr_button_apply->getScale().y, 
		m_system->m_width/2 + spr_button_apply->getSize().x*spr_button_apply->getScale().x, (m_system->m_height/9)*7 - 32*scale.y);

	fnt_options = m_system->m_font_manager->getFont("MTCORSVA.TTF");

	m_vsync = m_system->m_vsync;
	m_fullscreen = m_system->m_fullscreen;

	// GET CURRENT RESOLUTION
	int counter = -1;
	for(auto& res: m_system->m_video_modes)
	{
		counter++;
		if (res.height == m_system->m_height 
			&& res.width == m_system->m_width
			&& res.bitsPerPixel == m_system->m_bit)
		{
			m_resolution = counter;
			break;
		}
	}

	if(m_vsync)
	{
		spr_checkbox_vsync->setFrame(1);
	}else{
		spr_checkbox_vsync->setFrame(0);
	}

	if(m_fullscreen)
	{
		spr_checkbox_fullscreen->setFrame(1);
	}else{
		spr_checkbox_fullscreen->setFrame(0);
	}

	m_vol = m_system->m_volume*10;
	spr_volume_bar->setFrame(m_vol);

	/*#pragma region Volume Buttons
	spr_buttons_volume = m_system->m_sprite_manager->getSprite("Options/empty.png",0,0,45,128);
	spr_buttons_volume->setScale(scale.x, scale.y);

	for(int i = 0; i < 10; i++)
	{
		m_buttons_volume[i] = new Button(spr_buttons_volume, spr_buttons_volume->getSize().x, spr_buttons_volume->getSize().y,
			spr_volume_bar->getPosition().x + (spr_buttons_volume->getSize().x * i + 1), spr_volume_bar->getPosition().y);
	}
	#pragma endregion*/

	return true;
}
void OptionsState::Exit()
{
	std::cout << "  " << m_name << "->";

	delete spr_background;
	spr_background = nullptr;

	delete spr_button_resolutiondown;
	spr_button_resolutiondown = nullptr;

	delete spr_button_resolutionup;
	spr_button_resolutionup = nullptr;

	delete spr_volume_bar;
	spr_volume_bar = nullptr;

	delete spr_button_volumedown;
	spr_button_volumedown = nullptr;

	delete spr_button_volumeup;
	spr_button_volumeup = nullptr;

	delete m_button_volumedown;
	m_button_volumedown = nullptr;

	delete m_button_volumeup;
	m_button_volumeup = nullptr;

	delete m_button_fullscreen;
	m_button_fullscreen = nullptr;

	delete spr_checkbox_fullscreen;
	spr_checkbox_fullscreen = nullptr;

	delete m_button_vsync;
	m_button_vsync = nullptr;

	delete spr_checkbox_vsync;
	spr_checkbox_vsync = nullptr;

	delete spr_button_apply;
	spr_button_apply = nullptr;

	delete spr_button_back;
	spr_button_back = nullptr;

	delete m_button_apply;
	m_button_apply = nullptr;

	delete m_button_back;
	m_button_back = nullptr;

	/*for(int i = 0; i < 10; i++)
	{
		delete m_buttons_volume[i];
		m_buttons_volume[i] = nullptr;
	}

	delete spr_buttons_volume;
	spr_buttons_volume = nullptr;*/

	delete object_manager;
	object_manager = nullptr;

	m_paused = false;
}

void OptionsState::Pause()
{
	m_paused = true;
}

void OptionsState::Resume()
{
	m_paused = false;
}

bool OptionsState::Update(float _deltatime){
	//std::cout << "OptionsState::Update" << std::endl;
	
/*
	switch(state)
	{
	case 0:
		if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Space))
		{
			state = 1;
		}
	case 1:
		m_next = "MenuState";
		return false;
		break;
	}
*/
	/*if (m_system->m_keyboard->IsDownOnce(sf::Keyboard::Q))
	{
        m_next = "";
		return false;
	}*/

	if(m_vol > 0)
	{
		if(m_button_volumedown->Update(_deltatime, m_system->m_mouse))
		{
			m_vol -= 1;
			spr_volume_bar->setFrame(m_vol);
		}
	}
	if(m_vol < 10)
	{
		if(m_button_volumeup->Update(_deltatime, m_system->m_mouse))
		{
			m_vol += 1;
			spr_volume_bar->setFrame(m_vol);
		}
	}

	if(m_resolution > 0)
	{
		if(m_button_resolutionup->Update(_deltatime, m_system->m_mouse))
		{
			m_resolution -= 1;

			//std::cout << m_system->m_video_modes[m_resolution].width << 'x' << m_system->m_video_modes[m_resolution].height;
		}
	}
	if(m_resolution < m_system->m_video_modes.size() - 1)
	{
		if(m_button_resolutiondown->Update(_deltatime, m_system->m_mouse))
		{
			m_resolution += 1;

			//std::cout << m_system->m_video_modes[m_resolution].width << 'x' << m_system->m_video_modes[m_resolution].height;
		}
	}

	// APPLY
	if(m_button_apply->Update(_deltatime, m_system->m_mouse))
	{
		m_system->m_volume = m_vol/10;
		
		m_system->m_fullscreen = m_fullscreen;
		m_system->m_vsync = m_vsync;

		m_system->m_width = m_system->m_video_modes[m_resolution].width;
		m_system->m_height = m_system->m_video_modes[m_resolution].height;
		m_system->m_bit = m_system->m_video_modes[m_resolution].bitsPerPixel;

		m_system->setVideoMode();
		m_next = "MenuState";
		return false;
	}

	if(m_button_back->Update(_deltatime, m_system->m_mouse))
	{
		m_next = "";
		return false;
	}

	if(m_button_fullscreen->Update(_deltatime, m_system->m_mouse))
	{
		spr_checkbox_fullscreen->setFrame(!spr_checkbox_fullscreen->getFrame());
		m_fullscreen = !m_fullscreen;
	}

	if(m_button_vsync->Update(_deltatime, m_system->m_mouse))
	{
		spr_checkbox_vsync->setFrame(!spr_checkbox_vsync->getFrame());
		m_vsync = !m_vsync;
	}

	return true;
}

void OptionsState::Draw(){
	//std::cout << "OptionsState::Draw" << std::endl;

	//m_system->m_window->setView(m_system->m_window->getDefaultView());

	// BLACK FADE
	sf::RectangleShape rect_fade(sf::Vector2f(m_system->m_width, m_system->m_height));
	rect_fade.setFillColor(sf::Color(0,0,0,128));

	m_system->m_window->draw(rect_fade);

	//m_system->m_window->draw(*spr_background);

	m_system->m_window->draw(*spr_volume_bar);
	//m_system->m_window->draw(*spr_text_vsync);
	//m_system->m_window->draw(*spr_text_fullscreen);
	//m_system->m_window->draw(*spr_text_resolution);

	m_button_volumedown->getSprite()->setOpacity(255);
	m_button_volumedown->Draw(m_system->m_window);
	m_button_volumeup->getSprite()->setOpacity(255);
	m_button_volumeup->Draw(m_system->m_window);

	m_button_fullscreen->getSprite()->setOpacity(255);
	m_button_fullscreen->Draw(m_system->m_window, 1);
	m_button_vsync->getSprite()->setOpacity(255);
	m_button_vsync->Draw(m_system->m_window, 1);

	m_button_apply->getSprite()->setOpacity(255);
	m_button_apply->Draw(m_system->m_window);
	m_button_back->getSprite()->setOpacity(255);
	m_button_back->Draw(m_system->m_window);

	// RESOLUTION TEXT
	std::string txt = std::to_string(m_system->m_video_modes[m_resolution].width) + "x"
		+ std::to_string(m_system->m_video_modes[m_resolution].height) + " "
		+ std::to_string(m_system->m_video_modes[m_resolution].bitsPerPixel) + "bit";

	sf::Text txt_res;
	txt_res.setFont(*fnt_options);
	txt_res.setString(txt);
	txt_res.setCharacterSize(48);
	txt_res.setColor(sf::Color(125,118,99));
	
	txt_res.setPosition(m_system->m_width/2 - txt_res.getLocalBounds().width/2,m_system->m_height/2 - 250.f);

	m_system->m_window->draw(txt_res);

	m_button_resolutiondown->getSprite()->setOpacity(255);
	m_button_resolutiondown->Draw(m_system->m_window);
	m_button_resolutionup->getSprite()->setOpacity(255);
	m_button_resolutionup->Draw(m_system->m_window);

//	object_manager->Draw(m_system->m_window);
}

std::string OptionsState::Next(){
	//std::cout << "OptionsState::next" << std::endl;
	return m_next;
}

bool OptionsState::IsType(const std::string &type) {
	return type.compare(m_name) == 0;
}

bool OptionsState::isPaused()
{
	return m_paused;
}

bool OptionsState::isBase()
{
	return m_base;
}