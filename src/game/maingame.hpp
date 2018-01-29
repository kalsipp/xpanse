#pragma once
#include "../engine/engine.hpp"
#include "../engine/inputmanager.hpp"
#include "../engine/resourcemanager.hpp"
#include "../engine/basics/vector2d.hpp"
#include "resource_paths.hpp"
#include "scenes/mainscene.hpp"
class MainGame {
public:
	static void initialize();
	static void mainloop();
	static void teardown();
private:
	static bool m_initialized;
	MainGame();
	Transform m_world_position;
};