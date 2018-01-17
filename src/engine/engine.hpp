#pragma once


#include "basics/logging.hpp"

#include <thread>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
#include <typeinfo>
#include <signal.h> 
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory>

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
	static std::weak_ptr<gameobject_type> add_gameobject();
	template <class gameobject_type>
	static std::weak_ptr<gameobject_type> get_gameobject(const GAMEOBJECT_ID);
	static std::weak_ptr<GameObject> get_gameobject(const GAMEOBJECT_ID);
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
	static void run_setups(std::vector<std::shared_ptr<GameObject>> & );
	static bool m_running;
	static bool m_initialized;
	static std::thread m_enginethread;
	static std::map<GAMEOBJECT_ID, std::shared_ptr<GameObject>> m_gameobjects;
	static std::queue<std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>>> m_gameobjects_to_add;
	static std::queue<GAMEOBJECT_ID> m_gameobjects_to_remove;
	static GAMEOBJECT_ID m_latest_gameobject_id;
	
	friend void dynamic_cast_gameobject(); //for testing
};

template <class gameobject_type>
std::weak_ptr<gameobject_type> Engine::add_gameobject() {
	GAMEOBJECT_ID id = Engine::m_latest_gameobject_id;
	std::shared_ptr<gameobject_type> new_object = std::make_shared<gameobject_type>(id);
	if (Engine::m_latest_gameobject_id == std::numeric_limits<int>::max()) {
		Logging::log(Logging::WARNING, "Warning, gameobject id overflow");
	}
	std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>> pair = std::make_pair(id, new_object);
	Engine::m_gameobjects_to_add.push(pair);
	++Engine::m_latest_gameobject_id;
	Logging::log(Logging::TRACE, "Added gameobject id " + std::to_string(id) + " type " + typeid(gameobject_type).name());
	return new_object;
}

template <class gameobject_type>
std::weak_ptr<gameobject_type> Engine::get_gameobject(const GAMEOBJECT_ID id) {
	assert(Engine::m_gameobjects.count(id));
	if (!Engine::m_gameobjects.count(id)) return std::shared_ptr<gameobject_type>(); //null
    return std::static_pointer_cast<gameobject_type>(Engine::m_gameobjects[id]);
}
