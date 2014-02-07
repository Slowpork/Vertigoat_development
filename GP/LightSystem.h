// LightSystem.h

#include <vector>

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Font.hpp"

struct Segment;

namespace sf
{
	class RectangleShape;
	class ConvexShape;
	class VertexArray;
	class Font;
	class RenderWindow;
}

// This struct stores an edge or a segment
struct EndPoint
{
	float x;
	float y;
	bool begin;
	Segment* segment;
	float angle;
	bool visualize;
};

struct Segment
{
	EndPoint* a;
	EndPoint* b;
	float d;
};

struct Points
{
	sf::Vector2f point1;
	sf::Vector2f point2;
	sf::Vector2f point3;
	sf::Vector2f point4;
};

class LightSystem
{
public:

	LightSystem(sf::RenderWindow* _window);
	~LightSystem();

	void run();

	void logic();
	void render();

	void AttachState(State* state);
	void ChangeState();

	// Load the edges of the outside perimeter
	void loadEdgeOfMap(sf::Vector2f position, sf::Vector2f size);

	// Load whole map with walls and map edge
	void loadMap(sf::Vector2f position, sf::Vector2f size);

	// Adds an edge to the edges vector
	void addSegment(float x1, float y1, float x2, float y2);

	// Set location of guard
	// Segment and EndPoint data can't be processed until the guard location is known
	void setLightLocation(float x, float y);

	bool cursorInside(sf::Vector2f pos, sf::Vector2f size);

	void sweep();
	bool _segment_in_front_of(Segment* a, Segment* b, sf::Vector2f relativeTo);

	bool leftOf(Segment* a, sf::Vector2f point);

	void Createwall(sf::Vector2f pos, sf::Vector2f size);

	// Max, min functions
	//float min(float a, float b) { return (a < b) ? a : b; }
	//float max(float a, float b) { return (a > b) ? a : b; }

private:

	void LightSystem::addTriangle(float angle1, float angle2, Segment* segment);
	sf::Vector2f interpolate(sf::Vector2f p, sf::Vector2f q, float f);
	sf::Vector2f LinesIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4);

private:

	std::vector<State*> states;
	State* current;

	sf::Vector2f light_pos;

	std::vector<Points*> points;

	std::vector<Segment*> segments;
	std::vector<Segment*> open;
	std::vector<EndPoint*> endPoints;

	sf::Vector2f center; // Light center
	sf::VertexArray field_of_view;

	std::vector<sf::Vertex> light;

	sf::RenderWindow* mWindow;
};