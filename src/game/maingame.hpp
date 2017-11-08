#pragma once
#include "../engine/inputmanager.hpp"
#include "../engine/engine.hpp"
#include "staticobject.hpp"
class MainGame {
public:
	static void initialize();
	static void mainloop();
	static void teardown();
private:
	static bool m_running;
	static bool m_initialized;
	MainGame();
};