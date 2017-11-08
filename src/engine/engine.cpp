#include "engine.hpp"





bool Engine::m_initialized = false;
bool Engine::m_running = false;
std::thread Engine::m_enginethread;
std::map<GAMEOBJECT_ID, GameObject*> Engine::m_gameobjects;
GAMEOBJECT_ID Engine::m_latest_gameobject_id = 0;


void Engine::initialize() {
	assert(!Engine::m_initialized);
	Engine::m_initialized = true;
	GraphicsManager::initialize();
	InputManager::initialize();
}

void Engine::teardown() {
	GraphicsManager::teardown();
}

void Engine::start() {
	assert(Engine::m_initialized);
	Engine::m_running = true;
	Engine::m_enginethread =  std::thread(&Engine::update);
}

void Engine::stop() {
	Engine::m_running = false;
	Engine::m_enginethread.join();
}

GAMEOBJECT_ID Engine::add_gameobject(GameObject * new_object) {
	Engine::m_gameobjects[Engine::m_latest_gameobject_id] = new_object;
	GAMEOBJECT_ID id = Engine::m_latest_gameobject_id;
	if (Engine::m_latest_gameobject_id == std::numeric_limits<int>::max()) {
		std::cerr << "Warning, gameobject id overflow" << std::endl;
	}
	++Engine::m_latest_gameobject_id;
	return id;
}

void Engine::remove_gameobject(GAMEOBJECT_ID id) {
	assert(Engine::m_gameobjects.count(id));
	delete Engine::m_gameobjects[id];

	Engine::m_gameobjects.erase(id);
}

void Engine::update() {
	while (Engine::m_running) {
		InputManager::read_inputs();
		Engine::update_gameobjects();
		Engine::render_gameobjects();
	}
}

void Engine::update_gameobjects() {
	for (auto i = Engine::m_gameobjects.begin(); i != Engine::m_gameobjects.end(); ++i) {
		(*i).second->update();
	}
}

void Engine::render_gameobjects() {
	Engine::sort_gameobjects();
	GraphicsManager::prepare_rendering();
	for (auto i = m_gameobjects.begin(); i != m_gameobjects.end(); ++i) {
		(*i).second->render();
	}
	GraphicsManager::execute_rendering();
}

bool compare_gameobjects(const std::pair<GAMEOBJECT_ID, GameObject*>& a, const std::pair<GAMEOBJECT_ID, GameObject*>& b) {
	return (a.second->position().z < b.second->position().z);
}

void Engine::sort_gameobjects() {
	// std::vector<std::pair<K, V>> items;

	// //fill items
	// for(auto i = m_gameobjects.begin(); i != m_gameobjects.end(); ++i){

	// }
	// //sort by value using std::sort
	// std::sort(items.begin(), items.end(), value_comparer);

	// //sort by key using std::stable_sort
	// std::stable_sort(items.begin(), items.end(), key_comparer);

}