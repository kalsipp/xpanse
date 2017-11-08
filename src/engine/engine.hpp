#pragma once
#include <thread>
#include <vector>
#include <limits>
#include <algorithm>
#include "graphicsmanager.hpp"
#include "gameobject.hpp"
#include "inputmanager.hpp"

typedef unsigned long GAMEOBJECT_ID;

class Engine {
public:
	static void initialize();
	static void teardown();
	static void start();
	static void stop();
	static GAMEOBJECT_ID add_gameobject(GameObject *);
	static void remove_gameobject(GAMEOBJECT_ID id);
private:
	Engine();
	static void update();
	static void update_gameobjects();
	static void render_gameobjects();
	static void sort_gameobjects();
	static bool m_running;
	static bool m_initialized;
	static std::thread m_enginethread;
	static std::map<GAMEOBJECT_ID, GameObject*> m_gameobjects;
	static GAMEOBJECT_ID m_latest_gameobject_id;
	friend void engine_test();
};