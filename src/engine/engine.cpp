#include "engine.hpp"

#include "components/debug_closegamecomponent.hpp"



bool Engine::m_initialized = false;
bool Engine::m_running = false;
std::thread Engine::m_enginethread;
std::map<GAMEOBJECT_ID, GameObject*> Engine::m_gameobjects;
GAMEOBJECT_ID Engine::m_latest_gameobject_id = 0;
std::queue<std::pair<GAMEOBJECT_ID, GameObject*>> Engine::m_gameobjects_to_add;
std::queue<GAMEOBJECT_ID> Engine::m_gameobjects_to_remove;



void set_up_logging() {
	Logging::add_file("logs/everything.log", Logging::TRACE);
	Logging::add_file("logs/info.log", Logging::INFO);
	Logging::add_file("logs/warnings.log", Logging::WARNING);
	Logging::add_file("logs/errors.log", Logging::ERROR);
	Logging::log(Logging::INFO, "NICE LOGGING");
}



/* Public routines */
void Engine::initialize() {
	ASSERT(!Engine::m_initialized, "You can't initialize engine twice!");
	set_up_logging();
	GraphicsManager::initialize();
	InputManager::initialize();
	Engine::add_gameobject<GameObject>().add_component<Debug_CloseGameComponent>();
	Engine::m_initialized = true;
	Logging::log(Logging::INFO, "Finished initialize Engine");
}

void Engine::teardown() {
	GraphicsManager::teardown();
	for(auto it = m_gameobjects.begin(); it != m_gameobjects.end(); ++it){
		delete (*it).second;
	}
	Logging::log(Logging::INFO, "Finished teardown Engine");
	Logging::teardown();
}

void Engine::start() {
	ASSERT(Engine::m_initialized, "You need to initialize engine first!");
	Engine::m_running = true;
	Logging::log(Logging::INFO, "Starting Engine");
	Engine::update();
}

void Engine::stop() {
	Engine::m_running = false;
}

GameObject * Engine::get_gameobject(const GAMEOBJECT_ID id) {
	if (!Engine::m_gameobjects.count(id)) return nullptr;
	return Engine::m_gameobjects[id];
}

void Engine::remove_gameobject(const GAMEOBJECT_ID id) {

	Engine::m_gameobjects_to_remove.push(id);
	Logging::log(Logging::TRACE, "Removing gameobject id " + std::to_string(id));
}

unsigned long Engine::get_gameobject_count() {
	return Engine::m_gameobjects.size();
}

/* Private routines*/

void Engine::update() {
	while (Engine::m_running) {
		Engine::put_gameobjects_into_world();
		Engine::remove_gameobject_from_world();
		InputManager::read_inputs();
		Engine::update_gameobjects();
		Engine::render_gameobjects();
	}
}

void Engine::update_gameobjects() {
	for (auto i = Engine::m_gameobjects.begin(); i != Engine::m_gameobjects.end(); ++i) {
		(*i).second->update_components();
	}
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
	std::vector<std::pair<GAMEOBJECT_ID, GameObject *>> items;

	//fill items
	for (auto i = m_gameobjects.begin(); i != m_gameobjects.end(); ++i) {
		items.push_back(*i);
	}
	//sort by value using std::sort
	std::sort(items.begin(), items.end(), compare_gameobjects);

	//copy back
	for (auto i = items.begin(); i != items.end(); ++i) {
		m_gameobjects[(*i).first] = (*i).second;
	}
}

void Engine::put_gameobjects_into_world() {
	while (!Engine::m_gameobjects_to_add.empty()) {
		std::pair<GAMEOBJECT_ID, GameObject*> new_item = Engine::m_gameobjects_to_add.front();
		Engine::m_gameobjects_to_add.pop();
		Engine::m_gameobjects[new_item.first] = new_item.second;
	}
}
void Engine::remove_gameobject_from_world() {
	while (!Engine::m_gameobjects_to_remove.empty()) {
		GAMEOBJECT_ID id = Engine::m_gameobjects_to_remove.front();
		if (Engine::m_gameobjects.count(id)) {
			Engine::m_gameobjects_to_remove.pop();
			delete Engine::m_gameobjects[id];
			Engine::m_gameobjects.erase(id);
		}
	}
}
