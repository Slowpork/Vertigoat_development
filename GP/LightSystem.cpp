// LightSystem.cpp

#include "stdafx.h"
#include "LightSystem.h"

#include "SFML\Network.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"

#include "LightSystem.h"
#include "Random.h"
#include "Window.h"
#include "Math.h"
#include "Angle.h"
#include "Guard.h"
#include "Wall.h"
#include "InputManager.h"
#include <iostream>

//#include "boost\utility.hpp"
//#include "boost\assert.hpp"

#include "clipper.hpp"

#include <string>
#include <algorithm>

void LightSystem::Createwall(sf::Vector2f pos, sf::Vector2f size)
{
	Wall* wall2 = new Wall();
	wall2->setSize(size);
	wall2->setPosition(pos);
	wall2->setOutlineColor(sf::Color(0,0,0,0));
	wall2->setOutlineThickness(2);
	wall2->setFillColor(sf::Color(128, 128, 128, 255));
	walls.push_back(wall2);

	loadMap(sf::Vector2f(0.f, 0.f), sf::Vector2f(800.f, 600.f));
}

LightSystem::LightSystem()
{
	mWindow = new Window();
	mWindow->create(sf::VideoMode(mWindow->getScreenResolution().x, mWindow->getScreenResolution().y), mWindow->getTitle());
	mWindow->setFramerateLimit(60);

	mQuit = false;

	keyboard = new Keyboard();
	mouse = new Mouse();
	
	// Create the lightsource of the guard
	Guard* guard = new Guard();
	guard->setRadius(15.f);
	guard->setPosition(sf::Vector2f(mWindow->getScreenResolution().x / 2, mWindow->getScreenResolution().y / 2));
	guard->setFillColor(sf::Color(255, 255, 255));
	guard->setLengthOfSight(100.f);
	guard->setFov(500.f);
	guard->setPointCount(64);
	guard->setRotation(45.f);
	guard->setOrigin(15.f, 15.f);
	this->guard = guard;

	degrees = 0.f;

	start_pos.x = -1;
	start_pos.y = -1;
}

/*
LightSystem::~LightSystem()
{
	delete mWindow;
}

void LightSystem::run()
{
	Random::setRandomSeed();

	loadMap(sf::Vector2f(0.f, 0.f), sf::Vector2f(800.f, 600.f));

	font.loadFromFile("verdana.ttf");

	while (!mQuit){
		handleEvents();
		logic();
		render();
		keyboard->PostUpdate();
		mouse->PostUpdate();
	}
}
*/

void LightSystem::handleEvents()
{
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mQuit = true;
			mWindow->close();
		}
		if (event.type == sf::Event::KeyPressed)
			keyboard->current[event.key.code] = true;
		if (event.type == sf::Event::KeyReleased)
			keyboard->current[event.key.code] = false;
		if (event.type == sf::Event::MouseButtonPressed)
			mouse->current[event.mouseButton.button] = true;
		if (event.type == sf::Event::MouseButtonReleased)
			mouse->current[event.mouseButton.button] = false;
	}
}

void LightSystem::logic()
{
	guard->setPosition(sf::Vector2f(sf::Mouse::getPosition(*mWindow).x, sf::Mouse::getPosition(*mWindow).y));

	setGuardLocation(guard->getPosition().x, guard->getPosition().y);

	if ( !mouse->IsDown(Left))
	{
		if (start_pos.x != -1 && start_pos.y != -1 )
		{
			Createwall(sf::Vector2f(start_pos.x, start_pos.y)
			,sf::Vector2f( fabs(sf::Mouse::getPosition(*mWindow).x - start_pos.x), fabs(sf::Mouse::getPosition(*mWindow).y - start_pos.y)));
			start_pos.x = -1;
			start_pos.y = -1;

			std::cout << "yes" << std::endl;
		}
	}
	
	if ( mouse->IsDown(Left) )
	{
		if (start_pos.x == -1 && start_pos.y == -1)
		{
			start_pos = sf::Vector2f(sf::Mouse::getPosition(*mWindow).x, sf::Mouse::getPosition(*mWindow).y);
		}
	}

	sweep();
	processTriangle();
	//sf::Vector2i mouse_pos = sf::Mouse::getPosition(*mWindow);
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
	
	mWindow->clear(); // Clear the window
	mWindow->draw(*guard); // Draw the guard(light)

	

	bool inside = false;

	for (auto wall: walls) // Draw walls
	{
		if ( cursorInside(wall->getPosition(), wall->getSize()))
		{
			wall->setFillColor(sf::Color(128,128,128,128));
			wall->setOutlineColor(sf::Color(128,128,128,255));

			inside = true;
		}
		else
		{
			wall->setFillColor(sf::Color(128,128,128,255));
			wall->setOutlineColor(sf::Color(255,0,0,0));
		}

		mWindow->draw(*wall);
	}

	if ( !inside )
	{
		field_of_view.setPrimitiveType(sf::PrimitiveType::Triangles);
		//mWindow->draw(field_of_view); // Draw the light itself
		mWindow->draw(&light[0], static_cast<unsigned int>(light.size()), sf::PrimitiveType::TrianglesFan);
	}
	
	int counter = 0;
	for (int i = 0; i < endPoints.size(); i++)
	{
		if (endPoints.at(i)->visualize)
		{
			counter++;
			
			/*
			sf::CircleShape point;
			point.setRadius(3.f);
			point.setPosition(sf::Vector2f(endPoints.at(i)->x, endPoints.at(i)->y));
			point.setFillColor(sf::Color(255, 100, 0));
			point.setOrigin(3.f, 3.f);
			mWindow->draw(point);
			*/

			/*
			sf::Text text;
			text.setFont(font);
			text.setString(sf::String(std::to_string(counter)));
			text.setColor(sf::Color::Red);
			text.setPosition(sf::Vector2f(endPoints.at(i)->x, endPoints.at(i)->y));
			text.setCharacterSize(12);
			mWindow->draw(text);*/
		}
	}

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

	if ( mouse->IsDown(Left))
	{
		sf::RectangleShape rect(sf::Vector2f( 
			fabs(sf::Mouse::getPosition(*mWindow).x - start_pos.x), 
			fabs(sf::Mouse::getPosition(*mWindow).y - start_pos.y)));
		rect.setOutlineColor(sf::Color::Red);
		rect.setPosition(sf::Vector2f(start_pos.x,start_pos.y));
		rect.setOutlineThickness(2.f);
		rect.setFillColor(sf::Color(40,60,80,128));
		
		mWindow->draw(rect);
	}


	mWindow->display();
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
	for (auto wall : walls)
	{
		addSegment(wall->getPosition().x , wall->getPosition().y , wall->getPosition().x + wall->getSize().x , wall->getPosition().y ); // Upper left to upper right
		addSegment(wall->getPosition().x + wall->getSize().x , wall->getPosition().y , wall->getPosition().x + wall->getSize().x , wall->getPosition().y + wall->getSize().y ); // Upper right to lower right
		addSegment(wall->getPosition().x + wall->getSize().x , wall->getPosition().y + wall->getSize().y , wall->getPosition().x , wall->getPosition().y + wall->getSize().y ); // Lower right to lower left
		addSegment(wall->getPosition().x , wall->getPosition().y + wall->getSize().y , wall->getPosition().x , wall->getPosition().y ); // Lower left to upper left
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

void LightSystem::setGuardLocation(float x, float y)
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

sf::Vector2f RotatePoint(sf::Vector2f pointToRotate, sf::Vector2f centerPoint, double angleInDegrees)
{
	double angleInRadians = angleInDegrees * (3.1415f / 180.f);
	double cosTheta = cosf(angleInRadians);
	double sinTheta = sinf(angleInRadians);
	return sf::Vector2f((cosTheta * (pointToRotate.x - centerPoint.x) -
		sinTheta * (pointToRotate.y - centerPoint.y) + centerPoint.x),
		(sinTheta * (pointToRotate.x - centerPoint.x) +
		cosTheta * (pointToRotate.y - centerPoint.y) + centerPoint.y)
		);
}

void LightSystem::sweep()
{
	std::sort(endPoints.begin(), endPoints.end(), sortEndPoints);

	field_of_view.clear(); // Clear all vertex becuase we will have new ones from our addTriangle();
	open.clear();
	lightPoly.clear();
	float startingAngle = 0.f;

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
					//it = boost::next(it);
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

	// Create the guards vision or FoV
	ClipperLib::Path maskPoly;
	maskPoly.clear();

	float cone_length = 800.f;
	float cone_width = 2000000.f;

	sf::Vector2f p1(/*guard->getPosition().x * 1000.f*/50.f, guard->getPosition().y * 1000.f);
	sf::Vector2f p2((cone_length + guard->getPosition().x) * 1000.f, (-cone_width + guard->getPosition().y) * 1000.f);
	sf::Vector2f p3((cone_length + 50.f + guard->getPosition().x) * 1000.f, (guard->getPosition().y) * 1000.f);
	sf::Vector2f p4((cone_length + guard->getPosition().x) * 1000.f, (cone_width + guard->getPosition().y) * 1000.f);

	/*sf::Vector2f p1(50, 50);
	sf::Vector2f p2(600, 50);
	sf::Vector2f p3(600, 400);
	sf::Vector2f p4(50,400);*/

	/*p2 = RotatePoint(p2, p1, degrees);
	p3 = RotatePoint(p3, p1, degrees);
	p4 = RotatePoint(p4, p1, degrees);*/
	//degrees += 1;

	maskPoly.emplace_back(p1.x, p1.y);
	maskPoly.emplace_back(p2.x, p2.y);
	maskPoly.emplace_back(p3.x, p3.y);
	maskPoly.emplace_back(p4.x, p4.y);

	/*maskPoly.emplace_back(51.f,51.f);
	maskPoly.emplace_back(600,51.f);
	maskPoly.emplace_back(51.f,600);
	maskPoly.emplace_back(500,500);*/

	// Create the clipper object
	ClipperLib::Clipper clipper;
	clipper.AddPath(lightPoly, ClipperLib::ptSubject, true);
	clipper.AddPath(maskPoly, ClipperLib::ptClip, true);

	ClipperLib::Paths output;

	// And this row executes the cutting
	clipper.Execute(ClipperLib::ctIntersection, output, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

	light.clear();
	light.emplace_back(sf::Vector2f(guard->getPosition().x, guard->getPosition().y), sf::Color(255, 255, 128, 192));
	
	if (!output.empty())
	{
		ClipperLib::Path &path = output[0];

		for (ClipperLib::IntPoint &point : path)
		{
			sf::Vector2f tp(static_cast<float>(point.X) / 1000.f, static_cast<float>(point.Y) / 1000.f);
			light.emplace_back(tp, sf::Color(255, 255, 128, 192));
		}
		{
			ClipperLib::IntPoint &point = path[0];
			sf::Vector2f tp(static_cast<float>(point.X) / 1000.f, static_cast<float>(point.Y) / 1000.f);
			light.emplace_back(tp, sf::Color(255, 255, 128, 192));
		}
	}
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

	lightPoly.emplace_back(tp1.x * 1000.f + guard->getPosition().x, tp1.y * 1000.f + guard->getPosition().y);
	lightPoly.emplace_back(tp2.x * 1000.f + guard->getPosition().x, tp2.y * 1000.f + guard->getPosition().y);
	field_of_view.LightSystemend(middle);
	field_of_view.LightSystemend(begin);
	field_of_view.LightSystemend(end);
}

void LightSystem::processTriangle()
{
	
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