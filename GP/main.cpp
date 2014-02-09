// main.cpp

#include "stdafx.h"
#include "Engine.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Engine engine;
	if( engine.Init() )
	{
		engine.Run();
		engine.Cleanup();
	}

	

	return 0;
}