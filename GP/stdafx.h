//stdafx.h

#pragma once

#include <sdkddkver.h>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include "Math.h"
#include "Random.h"

#include "ObjectManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "FileManager.h"
#include "CollisionManager.h"

#include "GameObject.h"
#include "Collider.h"

#include "PlayerObject.h"

#include "State.h"
#include "LoadingState.h"
#include "MenuState.h"
#include "OptionsState.h"
#include "GameState.h"

#include "Engine.h"
#include "System.h"


#pragma warning(disable:4099)
#define SFML_STATIC
#if defined(_DEBUG)
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-graphics-s-d.lib")
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "sfml-audio-s-d.lib")
#pragma comment(lib, "sfml-main-d.lib")
#else
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "sfml-audio-s.lib")
#pragma comment(lib, "sfml-main.lib")
#endif

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Audio.hpp>