// LightSystem.cpp

#include "stdafx.h"
#include "LightSystem.h"

#include "Random.h"
#include "Math.h"
#include <iostream>

#include <string>
#include <algorithm>

void LightSystem::Createwall(sf::Vector2f pos, sf::Vector2f size)
{
	Points *point = new Points();
	point->point1 = sf::Vector2f(pos.x, pos.y);
	point->point2 = sf::Vector2f(pos.x + size.x, pos.y);
	point->point3 = sf::Vector2f(pos.x, pos.y + size.y);
	point->point4 = sf::Vector2f(pos.x + size.x, pos.y + size.y);

	points.push_back(point);

	loadMap(sf::Vector2f(0.f, 0.f), sf::Vector2f(800.f, 600.f));
}

LightSystem::LightSystem(sf::RenderWindow* _window)
{
	mWindow = _window;
	
	// Create the lightsource of the guard
	light_pos = sf::Vector2f(0.f,0.f);
}

/*
LightSystem::~LightSystem()
{
	
}
*/

void LightSystem::logic()
{
	sweep();
}

bool LightSystem::cursorInside(sf::Vector2f pos, sf::Vector2f size)
{
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*mWindow).x, sf::Mouse::getPosition(*mWindow).y);
	if ( mouse_pos.x > pos.x && mouse_pos.x < pos.x + size.x )
	{
		if ( mouse_pos.y > pos.y && mouse_pos.y < pos.y + size.y)
		{
			return true;
		}
	}
	
	return false;
}

void LightSystem::render()
{
	/*mWindow->clear(); // Clear the window
	mWindow->draw(*guard); // Draw the guard(light)*/

	for (auto point: points) // FIX ME! draw walls
	{
		sf::RectangleShape rect(sf::Vector2f( 
			point->point2.x - point->point1.x, 
			point->point3.y - point->point1.y));
		rect.setOutlineColor(sf::Color::Red);
		rect.setPosition(point->point1);
		rect.setOutlineThickness(2.f);
		rect.setFillColor(sf::Color(40,60,80,128));

		mWindow->draw(rect);
	}

	field_of_view.setPrimitiveType(sf::PrimitiveType::Triangles);
	//mWindow->draw(field_of_view); // Draw the light itself
	mWindow->draw(&light[0], static_cast<unsigned int>(light.size()), sf::PrimitiveType::TrianglesFan);
	
	/*
	int counter = 0;
	for (int i = 0; i < endPoints.size(); i++)
	{
		if (endPoints.at(i)->visualize)
		{
			counter++;
			
			
			sf::CircleShape point;
			point.setRadius(3.f);
			point.setPosition(sf::Vector2f(endPoints.at(i)->x, endPoints.at(i)->y));
			point.setFillColor(sf::Color(255, 100, 0));
			point.setOrigin(3.f, 3.f);
			mWindow->draw(point);
			
			/*
			sf::Text text;
			text.setFont(font);
			text.setString(sf::String(std::to_string(counter)));
			text.setColor(sf::Color::Red);
			text.setPosition(sf::Vector2f(endPoints.at(i)->x, endPoints.at(i)->y));
			text.setCharacterSize(12);
			mWindow->draw(text);
		}
	}
	
	*/

	/*
	for (auto segment : segments)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(segment->a->x, segment->a->y)),
			sf::Vertex(sf::Vector2f(segment->b->x, segment->b->y))
		};

		mWindow->draw(line, 2, sf::Lines);
	}*/
}

void LightSystem::loadEdgeOfMap(sf::Vector2f position, sf::Vector2f size)
{
	addSegment(position.x, position.y, position.x + size.x, position.y); // Upper left to upper right
	addSegment(position.x + size.x, position.y, position.x + size.x, position.y + size.y); // Upper right to lower right
	addSegment(position.x + size.x, position.y + size.y, position.x, position.y + size.y); // Lower right to lower left
	addSegment(position.x, position.y + size.y, position.x, position.y); // Lower left to upper left
}

void LightSystem::loadMap(sf::Vector2f position, sf::Vector2f size)
{
	segments.clear();
	endPoints.clear();
	loadEdgeOfMap(sf::Vector2f(50.f, 50.f), sf::Vector2f(700.f, 500.f)); // Whole window
	for (auto point : points)
	{
		addSegment(point->point1.x , point->point1.y , point->point2.x , point->point2.y ); // Upper left to upper right
		addSegment(point->point2.x , point->point2.y , point->point3.x , point->point3.y ); // Upper right to lower right
		addSegment(point->point3.x , point->point3.y , point->point4.x , point->point4.y ); // Lower right to lower left
		addSegment(point->point4.x , point->point4.y , point->point1.x , point->point1.y ); // Lower left to upper left
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

void LightSystem::setLightLocation(float x, float y)
{
	center.x = x;
	center.y = y;

	for (auto segment : segments)
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

bool sortEndPoints(EndPoint* a, EndPoint* b)
{
	if (a->angle > b->angle)
		return false;
	if (a->angle < b->angle)
		return true;

	if (!a->begin && b->begin)
		return false;
	if (a->begin && !b->begin)
		return true;
	return false;
}

void LightSystem::sweep()
{
	std::sort(endPoints.begin(), endPoints.end(), sortEndPoints);

	field_of_view.clear(); // Clear all vertex becuase we will have new ones from our addTriangle();
	open.clear();
	float startingAngle = 0.0f;

	for (unsigned int i = 0; i <= 1; i++)
	{
		for (auto p : endPoints)
		{
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
					addTriangle(startingAngle, p->angle, current_old);
				}
				startingAngle = p->angle;
			}
		}
	}

	light.clear();
	light.emplace_back(light_pos, sf::Color(255, 255, 128, 192));
}

bool LightSystem::_segment_in_front_of(Segment* a, Segment* b, sf::Vector2f relativeTo)
{
	bool A1 = leftOf(a, interpolate(sf::Vector2f(b->a->x, b->a->y), sf::Vector2f(b->b->x, b->b->y), 0.01));
	bool A2 = leftOf(a, interpolate(sf::Vector2f(b->b->x, b->b->y), sf::Vector2f(b->a->x, b->a->y), 0.01));
	bool A3 = leftOf(a, relativeTo); 
	
	bool B1 = leftOf(b, interpolate(sf::Vector2f(a->a->x, a->a->y), sf::Vector2f(a->b->x, a->b->y), 0.01));
	bool B2 = leftOf(b, interpolate(sf::Vector2f(a->b->x, a->b->y), sf::Vector2f(a->a->x, a->a->y), 0.01));
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

	sf::Vertex middle(p1, sf::Color(255, 255, 255, 60));
	sf::Vertex begin(pBegin, sf::Color(255, 255, 255, 60));
	sf::Vertex end(pEnd, sf::Color(255, 255, 255, 60));

	sf::Transform inverse;
	sf::Vector2f tp1(inverse * pBegin), tp2(inverse * pEnd);

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