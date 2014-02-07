// LightSystem.h

#include <vector>

// Somehow I couldn't forward declare Vector2f :S
#include "SFML/System/Vector2.hpp"
#include "SFML\Graphics\VertexArray.hpp"
#include "SFML\Graphics\Font.hpp"

#include "clipper.hpp"

// FORWARD DECLARATION
class Window;
class State;
class Guard;
class Wall;
class Keyboard;
class Mouse;

struct Segment;

namespace sf
{
	class RectangleShape;
	class ConvexShape;
	class VertexArray;
	class Font;
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

class LightSystem
{
public:
	LightSystem();
	~LightSystem();

	void run();

	void handleEvents();
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
	void setGuardLocation(float x, float y);

	void processTriangle();

	bool cursorInside(sf::Vector2f pos, sf::Vector2f size);

	void sweep();
	bool _segment_in_front_of(Segment* a, Segment* b, sf::Vector2f relativeTo);

	bool leftOf(Segment* a, sf::Vector2f point);

	void Createwall(sf::Vector2f pos, sf::Vector2f size);

	sf::Vector2f interpolate(sf::Vector2f p, sf::Vector2f q, float f);

	sf::Vector2f LinesIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4);

	void LightSystem::addTriangle(float angle1, float angle2, Segment* segment);

	// Max, min functions
	float min(float a, float b) { return (a < b) ? a : b; }
	float max(float a, float b) { return (a > b) ? a : b; }

	float degrees;


private:
	std::vector<State*> states;
	State* current;

	sf::Vector2f start_pos;

	Guard* guard;

	std::vector<Wall*> walls;

	std::vector<Segment*> segments;
	std::vector<Segment*> open;
	std::vector<EndPoint*> endPoints;

	sf::Vector2f center; // Light center
	sf::VertexArray field_of_view;

	ClipperLib::Path lightPoly;
	std::vector<sf::Vertex> light;

	sf::Font font;

	Keyboard* keyboard;
	Mouse* mouse;

	bool mQuit;
	Window* mWindow;
};