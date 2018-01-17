#include "engine.hpp"

#include "components/debug_closegamecomponent.hpp"



bool Engine::m_initialized = false;
bool Engine::m_running = false;
std::thread Engine::m_enginethread;
std::map<GAMEOBJECT_ID, std::shared_ptr<GameObject>> Engine::m_gameobjects;
GAMEOBJECT_ID Engine::m_latest_gameobject_id = 0;
std::queue<std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>>> Engine::m_gameobjects_to_add;
std::queue<GAMEOBJECT_ID> Engine::m_gameobjects_to_remove;



void set_up_logging() {
	Logging::add_file("logs/everything.log", Logging::TRACE);
	Logging::add_file("logs/info.log", Logging::INFO);
	Logging::add_file("logs/warnings.log", Logging::WARNING);
	Logging::add_file("logs/errors.log", Logging::ERROR);
	Logging::log(Logging::INFO, "NICE LOGGING");
}

void set_up_stacktrace() {
	//Debug from helpers.hpp
	signal(SIGSEGV, sig_error_handler);
	signal(SIGABRT, sig_error_handler);
	signal(SIGINT, sig_error_handler);
}

/* Public routines */
void Engine::initialize() {
	ASSERT(!Engine::m_initialized, "You can't initialize engine twice!");
	set_up_stacktrace();
	set_up_logging();
	GraphicsManager::initialize();
	InputManager::initialize();
	auto g = Engine::add_gameobject<GameObject>();
	g.lock()->add_component<Debug_CloseGameComponent>();
	Engine::m_initialized = true;
	Logging::log(Logging::INFO, "Finished initialize Engine");
}

void Engine::teardown() {

	m_gameobjects.clear();

	//Clear out the queue.
	std::queue<std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>>>().swap(m_gameobjects_to_add);

	GraphicsManager::teardown();
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

std::weak_ptr<GameObject> Engine::get_gameobject(const GAMEOBJECT_ID id) {
	if (!Engine::m_gameobjects.count(id)) return std::shared_ptr<GameObject>();
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
	double ms_p_frame = 0.016666667*1000;
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

bool compare_gameobjects(const std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>>& a, const std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>>& b) {
	return (a.second->transform().get_position().z < b.second->transform().get_position().z);
}

void Engine::sort_gameobjects() {
	std::vector<std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>>> items;

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
	std::vector<std::shared_ptr<GameObject>> added_items(Engine::m_gameobjects_to_add.size());
	GAMEOBJECT_ID added_items_counter = 0;
	while (!Engine::m_gameobjects_to_add.empty()) {
		std::pair<GAMEOBJECT_ID, std::shared_ptr<GameObject>> new_item = Engine::m_gameobjects_to_add.front();
		Engine::m_gameobjects_to_add.pop();
		Engine::m_gameobjects[new_item.first] = new_item.second;
		added_items[added_items_counter] = new_item.second;
		++added_items_counter;
	}

	Engine::run_setups(added_items);
}
void Engine::remove_gameobject_from_world() {
	while (!Engine::m_gameobjects_to_remove.empty()) {
		GAMEOBJECT_ID id = Engine::m_gameobjects_to_remove.front();
		if (Engine::m_gameobjects.count(id)) {
			Engine::m_gameobjects_to_remove.pop();
			Engine::m_gameobjects.erase(id);
		}
	}
}


void Engine::run_setups(std::vector<std::shared_ptr<GameObject>> & gameobjects) {
	for (auto go = gameobjects.begin(); go != gameobjects.end(); ++go) {
		for (auto comp = (*go)->get_all_components().begin();
		        comp != (*go)->get_all_components().end();
		        ++comp) {
			(*comp)->setup(**go);
		}
	}
}

