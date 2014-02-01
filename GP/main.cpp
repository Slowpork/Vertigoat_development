// main.cpp

#include "stdafx.h"
#include "Engine.h"


int _tmain(int argc, _TCHAR* argv[])
{

	Engine engine;
	if(engine.initialize())
	{
		engine.runGame();
	}

	return 0;
}