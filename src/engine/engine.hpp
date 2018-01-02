#pragma once

#define NDEBUG

#include "basics/logging.hpp"

#include <thread>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <typeinfo>

#include "basics/timer.hpp"
#include "graphicsmanager.hpp"
#include "inputmanager.hpp"


typedef unsigned long GAMEOBJECT_ID;
#include "gameobject.hpp"

class GameObject;
class Engine {
public:
	static void initialize();
	static void teardown();
	static void start();
	static void stop();
	template <class gameobject_type>
	static GameObject & add_gameobject();
	static GameObject * get_gameobject(const GAMEOBJECT_ID);
	static void remove_gameobject(const GAMEOBJECT_ID id);
	static unsigned long get_gameobject_count();
private:
	Engine();
	static void update();
	static void update_gameobjects();
	static void render_gameobjects();
	static void sort_gameobjects();

	/*Actually puts the changes in place*/
	static void put_gameobjects_into_world();
	static void remove_gameobject_from_world();
	static bool m_running;
	static bool m_initialized;
	static std::thread m_enginethread;
	static std::map<GAMEOBJECT_ID, GameObject*> m_gameobjects;
	static std::queue<std::pair<GAMEOBJECT_ID, GameObject*>> m_gameobjects_to_add;
	static std::queue<GAMEOBJECT_ID> m_gameobjects_to_remove;
	static GAMEOBJECT_ID m_latest_gameobject_id;
};

template <class gameobject_type>
GameObject & Engine::add_gameobject() {
	GAMEOBJECT_ID id = Engine::m_latest_gameobject_id;
	GameObject * new_object = new gameobject_type(id);
	if (Engine::m_latest_gameobject_id == std::numeric_limits<int>::max()) {
		Logging::log(Logging::WARNING, "Warning, gameobject id overflow");
	}
	Engine::m_gameobjects_to_add.push(std::make_pair(id, new_object));
	++Engine::m_latest_gameobject_id;
	Logging::log(Logging::INFO, "Added gameobject id " + std::to_string(id) + " type " + typeid(gameobject_type).name());
	return *new_object;
}
