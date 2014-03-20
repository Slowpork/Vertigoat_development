//OptionsState.cpp

#include "OptionsState.h"

#include "Math.h"

#include <iostream>
#include <string>

#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\Font.hpp"
#include "SFML\Graphics\Text.hpp"
#include "SFML\System\String.hpp"

#include "System.h"

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
	m_textSize = 28;

	m_system = _system;
}

bool OptionsState::Enter(){
	std::cout << m_name << std::endl;

	//state = 0;

	sf::Vector2f scale = m_system->m_scale;

	spr_button_resolutiondown = m_system->m_sprite_manager->getSprite("Options/spr_button_resolution_low.png",0,0,128,128,2);
	spr_button_resolutiondown->setScale(0.5*scale.x, 0.5*scale.y);
	m_button_resolutiondown = new Button(spr_button_resolutiondown, spr_button_resolutiondown->getSize().x*spr_button_resolutiondown->getScale().x,
		spr_button_resolutiondown->getSize().y*spr_button_resolutiondown->getScale().y,
		m_system->m_width/2 - 250 * scale.x, m_system->m_height/2 - 230 * scale.y);

	spr_button_resolutionup = m_system->m_sprite_manager->getSprite("Options/spr_button_resolution_high.png",0,0,128,128,2);
	spr_button_resolutionup->setScale(0.5*scale.x,0.5*scale.y);
	m_button_resolutionup = new Button(spr_button_resolutionup, spr_button_resolutionup->getSize().x*spr_button_resolutionup->getScale().x,
		spr_button_resolutionup->getSize().y*spr_button_resolutionup->getScale().y,
		m_system->m_width/2 + 186 * scale.x, m_system->m_height/2 - 230 * scale.y);

	spr_volume_bar = m_system->m_sprite_manager->getSprite("Options/spr_volume_bars.png",0,0,456,128,10);
	spr_volume_bar->setScale(scale.x, 0.5*scale.y);
	spr_volume_bar->setPosition((m_system->m_width/2 - (spr_volume_bar->getSize().x*spr_volume_bar->getScale().x)/2),
		m_system->m_height/2 + 20);

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

	spr_checkbox_empty_fullscreen = m_system->m_sprite_manager->getSprite("Options/spr_checkbox_empty.png",0,0,128,128,2);
	spr_checkbox_empty_fullscreen->setScale(0.75*scale.x, 0.75*scale.y);
	spr_checkbox_checked_fullscreen = m_system->m_sprite_manager->getSprite("Options/spr_checkbox_checked.png",0,0,128,128,2);
	spr_checkbox_checked_fullscreen->setScale(0.75*scale.x, 0.75*scale.y);
	m_button_fullscreen = new Button(spr_checkbox_empty_fullscreen, 
		spr_checkbox_empty_fullscreen->getSize().x*spr_checkbox_empty_fullscreen->getScale().x,
		spr_checkbox_empty_fullscreen->getSize().y*spr_checkbox_empty_fullscreen->getScale().y, 
		m_system->m_width/2 + 150*scale.x, m_system->m_height/2 - 120*scale.y);

	spr_checkbox_empty_vsync = m_system->m_sprite_manager->getSprite("Options/spr_checkbox_empty.png",0,0,128,128,2);
	spr_checkbox_empty_vsync->setScale(0.75*scale.x, 0.75*scale.y);
	spr_checkbox_checked_vsync = m_system->m_sprite_manager->getSprite("Options/spr_checkbox_checked.png",0,0,128,128,2);
	spr_checkbox_checked_vsync->setScale(0.75*scale.x, 0.75*scale.y);
	m_button_vsync = new Button(spr_checkbox_empty_vsync, 
		spr_checkbox_empty_vsync->getSize().x*spr_checkbox_empty_vsync->getScale().x,
		spr_checkbox_empty_vsync->getSize().y*spr_checkbox_empty_vsync->getScale().y, 
		m_system->m_width/2 - 214*scale.x, m_system->m_height/2 - 120*scale.y);

	spr_button_back = m_system->m_sprite_manager->getSprite("Options/spr_button_return.png",0,0,219,64,2);
	spr_button_back->setScale(scale.x, scale.y);
	m_button_back = new Button(spr_button_back, spr_button_back->getSize().x*spr_button_back->getScale().x, 
		spr_button_back->getSize().y*spr_button_back->getScale().y, 
		m_system->m_width/2 - spr_button_back->getSize().x*spr_button_back->getScale().x,
		(m_system->m_height/9)*7 - 32*scale.y);

	spr_button_apply = m_system->m_sprite_manager->getSprite("Options/spr_button_apply.png",0,0,219,64,2);
	spr_button_apply->setScale(scale.x, scale.y);
	m_button_apply = new Button(spr_button_apply, spr_button_apply->getSize().x*spr_button_apply->getScale().x, 
		spr_button_apply->getSize().y*spr_button_apply->getScale().y, 
		m_system->m_width/2, (m_system->m_height/9)*7 - 32*scale.y);

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
		m_button_vsync->setSprite(spr_checkbox_checked_vsync);
	}else{
		m_button_vsync->setSprite(spr_checkbox_empty_vsync);
	}

	if(m_fullscreen)
	{
		m_button_fullscreen->setSprite(spr_checkbox_checked_fullscreen);
	}else{
		m_button_fullscreen->setSprite(spr_checkbox_empty_fullscreen);
	}

	m_vol = m_system->m_volume*10;
	spr_volume_bar->setFrame(m_vol);

	m_text_fullscreen.setString("Fullscreen");
	m_text_fullscreen.setFont(*fnt_options);
	m_text_fullscreen.setCharacterSize((int)(m_textSize*((scale.x + scale.y)/2)));
	m_text_fullscreen.setPosition(m_button_fullscreen->getPosition().x + 
		(m_button_fullscreen->getSize().x*scale.x)/2 - 
		(m_text_fullscreen.getLocalBounds().width/2),
		m_button_fullscreen->getPosition().y - m_text_fullscreen.getLocalBounds().height - 5*scale.y);
	m_text_fullscreen.setColor(sf::Color(155,148,129));

	m_text_resolution.setString("Resolution");
	m_text_resolution.setFont(*fnt_options);
	m_text_resolution.setCharacterSize((int)(m_textSize*((scale.x + scale.y)/2)));
	m_text_resolution.setPosition((m_system->m_width/2 - (m_text_resolution.getLocalBounds().width/2)),
		spr_button_resolutiondown->getPosition().y - m_text_resolution.getLocalBounds().height - 20*scale.y);
	m_text_resolution.setColor(sf::Color(155,148,129));

	m_text_volume.setString("Volume");
	m_text_volume.setFont(*fnt_options);
	m_text_volume.setCharacterSize((int)(m_textSize*((scale.x + scale.y)/2)));
	m_text_volume.setPosition(spr_volume_bar->getPosition().x + 
		(spr_volume_bar->getSize().x*spr_volume_bar->getScale().x)/2 - 
		(m_text_volume.getLocalBounds().width/2),
		spr_volume_bar->getPosition().y - m_text_volume.getLocalBounds().height - 20*scale.y);
	m_text_volume.setColor(sf::Color(155,148,129));

	m_text_vsync.setFont(*fnt_options);
	m_text_vsync.setString("Vsync");
	m_text_vsync.setCharacterSize((int)(m_textSize*((scale.x + scale.y)/2)));
	m_text_vsync.setPosition(m_button_vsync->getPosition().x + 
		(m_button_vsync->getSize().x*scale.x)/2 - (m_text_vsync.getLocalBounds().width/2),
		m_button_vsync->getPosition().y - m_text_vsync.getLocalBounds().height - 5*scale.y);
	m_text_vsync.setColor(sf::Color(155,148,129));

	/*#pragma region Volume Buttons
	spr_buttons_volume = m_system->m_sprite_manager->getSprite("Options/empty.png",0,0,45,128);
	spr_buttons_volume->setScale(scale.x, scale.y);

	for(int i = 0; i < 10; i++)
	{
		m_buttons_volume[i] = new Button(spr_buttons_volume, spr_buttons_volume->getSize().x, spr_buttons_volume->getSize().y,
			spr_volume_bar->getPosition().x + (spr_buttons_volume->getSize().x * i), spr_volume_bar->getPosition().y);
	}
	#pragma endregion*/

	return true;
}
void OptionsState::Exit()
{
	std::cout << "  " << m_name << "->";

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

	delete spr_checkbox_empty_fullscreen;
	spr_checkbox_empty_fullscreen = nullptr;

	delete spr_checkbox_checked_fullscreen;
	spr_checkbox_checked_fullscreen = nullptr;

	delete m_button_fullscreen;
	m_button_fullscreen = nullptr;

	delete spr_checkbox_empty_vsync;
	spr_checkbox_empty_vsync = nullptr;

	delete spr_checkbox_checked_vsync;
	spr_checkbox_checked_vsync = nullptr;

	delete m_button_vsync;
	m_button_vsync = nullptr;

	delete m_button_apply;
	m_button_apply = nullptr;

	delete m_button_back;
	m_button_back = nullptr;

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
		}
	}
	if(m_resolution < m_system->m_video_modes.size() - 1)
	{
		if(m_button_resolutiondown->Update(_deltatime, m_system->m_mouse))
		{
			m_resolution += 1;
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

	if(m_button_fullscreen->Update(_deltatime, m_system->m_mouse) && m_fullscreen)
	{
		m_button_fullscreen->setSprite(spr_checkbox_empty_fullscreen);
		m_fullscreen = !m_fullscreen;
	}else if(m_button_fullscreen->Update(_deltatime, m_system->m_mouse) && !m_fullscreen)
	{
		m_button_fullscreen->setSprite(spr_checkbox_checked_fullscreen);
		m_fullscreen = !m_fullscreen;
	}

	if(m_button_vsync->Update(_deltatime, m_system->m_mouse) && m_vsync)
	{
		m_button_vsync->setSprite(spr_checkbox_empty_vsync);
		m_vsync = !m_vsync;
	}else if(m_button_vsync->Update(_deltatime, m_system->m_mouse) && !m_vsync)
	{
		m_button_vsync->setSprite(spr_checkbox_checked_vsync);
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

	m_system->m_window->draw(*spr_volume_bar);

	m_button_volumedown->getSprite()->setOpacity(255);
	m_button_volumedown->Draw(m_system->m_window);
	m_button_volumeup->getSprite()->setOpacity(255);
	m_button_volumeup->Draw(m_system->m_window);
	m_button_fullscreen->Draw(m_system->m_window);
	m_button_vsync->Draw(m_system->m_window);

	m_button_fullscreen->getSprite()->setOpacity(255);
	m_button_fullscreen->Draw(m_system->m_window);
	m_button_vsync->getSprite()->setOpacity(255);
	m_button_vsync->Draw(m_system->m_window);

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
	txt_res.setCharacterSize((int)(48*((m_system->m_scale.x + m_system->m_scale.y)/2)));
	txt_res.setColor(sf::Color(125,118,99));
	
	txt_res.setPosition(m_system->m_width/2 - txt_res.getLocalBounds().width/2, m_system->m_height/2 - 235.f*m_system->m_scale.y);

	m_system->m_window->draw(txt_res);

	m_button_resolutiondown->getSprite()->setOpacity(255);
	m_button_resolutiondown->Draw(m_system->m_window);
	m_button_resolutionup->getSprite()->setOpacity(255);
	m_button_resolutionup->Draw(m_system->m_window);

	m_system->m_window->draw(m_text_fullscreen);
	m_system->m_window->draw(m_text_resolution);
	m_system->m_window->draw(m_text_volume);
	m_system->m_window->draw(m_text_vsync);
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