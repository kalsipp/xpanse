#pragma once
#include "../engine/inputmanager.hpp"
#include "../engine/engine.hpp"
#include "gameobjects/player.hpp"
#include "staticobject.hpp"
#include "image_paths.hpp"
class MainGame {
public:
	static void initialize();
	static void mainloop();
	static void teardown();
private:
	static bool m_initialized;
	MainGame();
};