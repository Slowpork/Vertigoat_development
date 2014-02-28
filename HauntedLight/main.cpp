// main.cpp

#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine engine;
	if( engine.Init() )
	{
		engine.Run();
		engine.Cleanup();
	}

	return EXIT_SUCCESS;
}