// LightSystem.cpp


#include "LightSystem.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Graphics\CircleShape.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\View.hpp"

#include "Random.h"
#include "Math.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "AnimatedSprite.h"

#include "System.h"

LightSystem::LightSystem(sf::RenderWindow* _window, sf::View* _view, ObjectManager* _object_manager, System* _system)
{
	m_window = _window;
	m_view = _view;
	m_object_manager = _object_manager;
	m_system = _system;

	mapPos = sf::Vector2f(0.f,0.f);
	mapSize = sf::Vector2f(1024.f,1024.f);
	
	// Create the lightsource of the guard
	light_pos = sf::Vector2f(0.f,0.f);
	light_color = sf::Color(255,255,255,255);
}

LightSystem::~LightSystem()
{
	for(auto segment: segments)
	{
		delete segment->a;
		segment->a = nullptr;
		delete segment->b;
		segment->b = nullptr;

		delete segment;
		segment = nullptr;
	}

	/*
	for(auto point: points)
	{
		delete point;
		point = nullptr;
	}*/
}

void LightSystem::addWall(sf::Vector2f pos, sf::Vector2f size)
{
	Points *point = new Points();
	point->point1 = sf::Vector2f(pos.x, pos.y);
	point->point2 = sf::Vector2f(pos.x + size.x, pos.y);
	point->point3 = sf::Vector2f(pos.x + size.x, pos.y + size.y);
	point->point4 = sf::Vector2f(pos.x, pos.y + size.y);

	points.push_back(point);

	//loadMap(sf::Vector2f(0.f, 0.f), sf::Vector2f(800.f, 600.f));
}

void LightSystem::logic()
{
	/*
	sf::Vector2f size = m_window->getView().getSize();
	size.x /= 2;
	size.y /= 2;
	size.x -= 128;
	size.y -= 128;
	sf::Vector2f _pos = m_window->getView().getCenter();
	
	addSegment(_pos.x - size.x, _pos.y - size.y, _pos.x + size.x, _pos.y - size.y);
	addSegment(_pos.x + size.x, _pos.y - size.y, _pos.x + size.x, _pos.y + size.y);
	addSegment(_pos.x + size.x, _pos.y + size.y, _pos.x - size.x, _pos.y + size.y);
	addSegment(_pos.x - size.x, _pos.y + size.y, _pos.x - size.x, _pos.y - size.y);*/
	
	sweep();
	update();

	/*
	deleteSegment(_pos.x - size.x, _pos.y - size.y, _pos.x + size.x, _pos.y - size.y);
	deleteSegment(_pos.x + size.x, _pos.y - size.y, _pos.x + size.x, _pos.y + size.y);
	deleteSegment(_pos.x + size.x, _pos.y + size.y, _pos.x - size.x, _pos.y + size.y);
	deleteSegment(_pos.x - size.x, _pos.y + size.y, _pos.x - size.x, _pos.y - size.y);*/
}

void LightSystem::Draw()
{
	/*m_window->clear(); // Clear the window
	m_window->draw(*guard); // Draw the guard(light)*/

	for (auto point: points) // FIX ME! draw walls
	{
		/*
		sf::RectangleShape rect(sf::Vector2f(
			point->point2.x - point->point1.x, 
			point->point3.y - point->point1.y));
		rect.setOutlineColor(sf::Color::Red);
		rect.setPosition(point->point1);
		rect.setOutlineThickness(2.f);
		rect.setFillColor(sf::Color(40,60,80,128));

		m_window->draw(rect);*/
	}

	//std::string txt = std::to_string(segments.size() / 2 ) + " light";
	//m_system->drawDebugText(sf::Vector2f(16,64),txt);

	field_of_view.setPrimitiveType(sf::PrimitiveType::Triangles);
	m_window->draw(field_of_view ,sf::BlendAlpha); // Draw the light itself
	//m_window->draw(&light[0], static_cast<unsigned int>(light.size()), sf::PrimitiveType::TrianglesFan);

	/*
	for (auto segment : segments)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(segment->a->x, segment->a->y)),
			sf::Vertex(sf::Vector2f(segment->b->x, segment->b->y))
		};

		m_window->draw(line, 2, sf::Lines);
	}*/
}

void LightSystem::setBounds(sf::Vector2f position, sf::Vector2f size)
{
	mapPos = position;
	mapSize = size;
	
	addSegment(position.x, position.y, position.x + size.x, position.y); // Upper left to upper right
	addSegment(position.x + size.x, position.y, position.x + size.x, position.y + size.y); // Upper right to lower right
	addSegment(position.x + size.x, position.y + size.y, position.x, position.y + size.y); // Lower right to lower left
	addSegment(position.x, position.y + size.y, position.x, position.y); // Lower left to upper left
	
}

void LightSystem::update()
{
	sf::Vector2f view_size = m_window->getView().getSize();
	view_size.x /= 2;
	view_size.y /= 2;
	//view_size.x -= 128;
	//view_size.y -= 128;
	sf::Vector2f view_pos = m_window->getView().getCenter();

	sf::Vector2f pos(view_pos.x - view_size.x,view_pos.y - view_size.y);
	sf::Vector2f size(view_size.x * 2,view_size.y * 2);

	segments.clear();
	endPoints.clear();
	setBounds(pos, size);
	
	for(auto& object: m_object_manager->m_objects)
	{
		//if (object.second->getDepth() == 5 )
		{
			sf::Vector2f point1(object.second->getPosition().x, object.second->getPosition().y);
			sf::Vector2f point2(object.second->getPosition().x + object.second->getSprite()->getSize().x, object.second->getPosition().y);
			sf::Vector2f point3(object.second->getPosition().x + object.second->getSprite()->getSize().x, object.second->getPosition().y + object.second->getSprite()->getSize().y);
			sf::Vector2f point4(object.second->getPosition().x, object.second->getPosition().y + object.second->getSprite()->getSize().y);
			
			if ( pointInside(pos,size,point1) || pointInside(pos,size,point2)
			||   pointInside(pos,size,point3) || pointInside(pos,size,point4))
			{
				addSegment(point1.x , point1.y , point2.x , point2.y ); // Upper left to upper right
				addSegment(point2.x , point2.y , point3.x , point3.y ); // Upper right to lower right
				addSegment(point3.x , point3.y , point4.x , point4.y ); // Lower right to lower left
				addSegment(point4.x , point4.y , point1.x , point1.y ); // Lower left to upper left
			}

			//std::cout << "woo";
		}
	}
}

void LightSystem::addSegment(float x1, float y1, float x2, float y2)
{
	Segment* segment = new Segment();
	EndPoint* p1 = new EndPoint();
	EndPoint* p2 = new EndPoint();

	segment->a = p1;
	segment->b = p2;
	segment->d = 0.f;

	p1->begin = false;
	p1->x = x1;
	p1->y = y1;
	p1->angle = 0.f;
	p1->segment = segment;
	p1->visualize = true;

	p2->begin = false;
	p2->x = x2;
	p2->y = y2;
	p2->angle = 0.f;
	p2->segment = segment;
	p2->visualize = false;

	segments.push_back(segment);
	endPoints.push_back(p1);
	endPoints.push_back(p2);
}

void LightSystem::deleteSegment(float x1, float y1, float x2, float y2)
{
	int pos = 0;
	for(auto& segment: segments)
	{
		if ( segment->a->x == x1 && segment->a->y == y1 
		  && segment->b->y == x2 && segment->b->y == y2)
		{
			delete segment;
			segment = nullptr;

			segments.erase(segments.begin() + pos);
			break;
		}
		pos++;
	}

	
	pos = 0;
	for(auto& endpoint: endPoints)
	{
		if ( endpoint->x == x1 && endpoint->y == y1 )
		{

			/*
			if (endpoint != nullptr)
			{
				delete endpoint;
				endpoint = nullptr;
			}
			*/

			endPoints.erase(endPoints.begin() + pos);
			break;
		}
		pos++;
	}
	
	pos = 0;
	for(auto& endpoint: endPoints)
	{
		if ( endpoint->x == x2 && endpoint->y == y2 )
		{
			/*
			if (endpoint != nullptr)
			{
				delete endpoint;
				endpoint = nullptr;
			}
			*/

			endPoints.erase(endPoints.begin() + pos);
			break;
		}
		pos++;
	}
}

void LightSystem::setLightLocation(float x, float y)
{
	center.x = x;
	center.y = y;

	for (auto& segment : segments)
	{
		float dx = 0.5f * (segment->a->x + segment->b->x) - x;
		float dy = 0.5f * (segment->a->y + segment->b->y) - y;

		segment->d = dx*dx + dy*dy;
		segment->a->angle = Math::atan2(segment->a->y - y, segment->a->x - x);
		segment->b->angle = Math::atan2(segment->b->y - y, segment->b->x - x);

		float dAngle = segment->b->angle - segment->a->angle;
		if (dAngle < -Math::PI) { dAngle += 2.f * Math::PI; }
		if (dAngle > Math::PI) { dAngle -= 2.f * Math::PI; }
		segment->a->begin = (dAngle > 0.0f);
		segment->b->begin = !segment->a->begin;
	}
}

sf::Vector2f LightSystem::getLightLocation()
{
	return center;
}

void LightSystem::setLightBrightness(float _value)
{
	float value = 2.55 * _value;
	light_color = sf::Color(value,value,value,255);
}

const float LightSystem::getLightBrightness() const
{
	return light_color.r;
}

bool sortEndPoints(EndPoint* a, EndPoint* b)
{
	if (a->angle > b->angle)
	{
		//std::cout << "false " << std::endl;
		return false;
	}
	if (a->angle < b->angle)
	{
		//std::cout << "true " << std::endl;
		return true;
	}
	if (!a->begin && b->begin)
	{
		//std::cout << "false " << std::endl;
		return false;
	}
	if (a->begin && !b->begin)
	{
		//std::cout << "true " << std::endl;
		return true;
	}
	//std::cout << "false " << std::endl;
	return false;
}

bool LightSystem::pointInside(sf::Vector2f _pos, sf::Vector2f _size, sf::Vector2f _point)
{
	if (_point.x > _pos.x && _point.x < _pos.x + _size.x &&
	   _point.y > _pos.y && _point.y < _pos.y + _size.y)
	{
		//std::cout << "What?";
		return true;
	}
	return false;
}

void LightSystem::sweep()
{
	std::sort(endPoints.begin(), endPoints.end(), sortEndPoints);

	field_of_view.clear(); // Clear all vertex becuase we will have new ones from our addTriangle();
	open.clear();
	float startingAngle = 0.0f;

	//std::cout << "####################################" << std::endl;

	for (unsigned int i = 0; i <= 1; i++)
	{
		for (auto& p : endPoints)
		{
			/*if (!pointInside(pos,size,sf::Vector2f(p->x,p->y)) )
				continue;*/

			//std::cout << "X:" << p->x << " Y: " << p->y << " begin: " << p->begin << std::endl;

			Segment* current_old = open.empty() ? nullptr : open.front();
			
			if (p->begin)
			{
				auto it = open.begin();
				while (it != open.end() && _segment_in_front_of(p->segment, (*it), sf::Vector2f(center.x, center.y)))
				{
					it++;
				}
				if (it == open.end())
				{
					open.push_back(p->segment);
				}
				else {
					open.insert(it, p->segment);
				}
			}
			else {
				std::vector<Segment*>::iterator it = std::find(open.begin(), open.end(), p->segment);
				if (it != open.end())
				{
					open.erase(it);
				}
			}

			Segment* current_new = open.empty() ? nullptr : open.front();
			if (current_old != current_new) {
				if (i == 1) {
					//std::cout << " add triangle" << std::endl;
					addTriangle(startingAngle, p->angle, current_old);
				}
				startingAngle = p->angle;
			}
		}
	}
}

bool LightSystem::_segment_in_front_of(Segment* a, Segment* b, sf::Vector2f relativeTo)
{
	bool A1 = leftOf(a, interpolate(sf::Vector2f(b->a->x, b->a->y), sf::Vector2f(b->b->x, b->b->y), 0.01f));
	bool A2 = leftOf(a, interpolate(sf::Vector2f(b->b->x, b->b->y), sf::Vector2f(b->a->x, b->a->y), 0.01f));
	bool A3 = leftOf(a, relativeTo); 
	
	bool B1 = leftOf(b, interpolate(sf::Vector2f(a->a->x, a->a->y), sf::Vector2f(a->b->x, a->b->y), 0.01f));
	bool B2 = leftOf(b, interpolate(sf::Vector2f(a->b->x, a->b->y), sf::Vector2f(a->a->x, a->a->y), 0.01f));
	bool B3 = leftOf(b, relativeTo);

	if (B1 == B2 && B2 != B3) return true;
	if (A1 == A2 && A2 == A3) return true;
	if (A1 == A2 && A2 != A3) return false;
	if (B1 == B2 && B2 == B3) return false;
	return false;
}

void LightSystem::addTriangle(float angle1, float angle2, Segment* segment)
{
	sf::Vector2f p1 = center;
	sf::Vector2f p2(center.x + Math::cos(angle1), center.y + Math::sin(angle1));
	sf::Vector2f p3(0.f, 0.f);
	sf::Vector2f p4(0.f, 0.f);

	if (segment != nullptr)
	{
		p3.x = segment->a->x;
		p3.y = segment->a->y;
		p4.x = segment->b->x;
		p4.y = segment->b->y;
	}
	else {
		p3.x = p1.x + Math::cos(angle1) * 500;
		p3.y = p1.y + Math::sin(angle1) * 500;
		p4.x = p1.x + Math::cos(angle2) * 500;
		p4.y = p1.y + Math::sin(angle2) * 500;
	}

	sf::Vector2f pBegin = LinesIntersection(p3, p4, p1, p2);

	p2.x = center.x + Math::cos(angle2);
	p2.y = center.y + Math::sin(angle2);
	sf::Vector2f pEnd = LinesIntersection(p3, p4, p1, p2);

	sf::Vertex middle(p1, light_color);
	sf::Vertex begin(pBegin, light_color);
	sf::Vertex end(pEnd, light_color);

	//sf::Transform inverse;
	//sf::Vector2f tp1(inverse * pBegin), tp2(inverse * pEnd);

	field_of_view.append(middle);
	field_of_view.append(begin);
	field_of_view.append(end);
}

bool LightSystem::leftOf(Segment* a, sf::Vector2f p)
{
	float cross = (a->b->x - a->a->x) * (p.y - a->a->y) - (a->b->y - a->a->y) * (p.x - a->a->x);
	return cross < 0;
}

sf::Vector2f LightSystem::interpolate(sf::Vector2f p, sf::Vector2f q, float f) {
	return sf::Vector2f(p.x*(1 - f) + q.x*f, p.y*(1 - f) + q.y*f);
}

sf::Vector2f LightSystem::LinesIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4) {
	float s = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x))
	/ ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
	return sf::Vector2f(p1.x + s * (p2.x - p1.x), p1.y + s * (p2.y - p1.y));
}