#include "maingame.hpp"

bool MainGame::m_initialized = false;

void MainGame::initialize() {
	if (!MainGame::m_initialized) {
		MainGame::m_initialized = true;
		Engine::initialize();
	}

	std::vector<GAMEOBJECT_ID> ids;
	for (uint i = 0; i < 100; ++i) {
		GAMEOBJECT_ID id = Engine::add_gameobject<StaticObject>().id();
		ids.push_back(id);
	}
	for (int i = 0; i < 50; ++i) {
		Engine::remove_gameobject(ids[i]);
	}
}

void MainGame::mainloop() {
	assert(MainGame::m_initialized);
	Engine::start();
}

void MainGame::teardown() {

}

