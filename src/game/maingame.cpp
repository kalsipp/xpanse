#include "maingame.hpp"

bool MainGame::m_initialized = false;

void MainGame::initialize() {
	if (!MainGame::m_initialized) {
		MainGame::m_initialized = true;
		Engine::initialize();
		GraphicsManager::load_texture(DEBUG_SMILEY);
		GraphicsManager::load_texture(PLAYER_SPRITE_SHEET);
	}

	std::vector<GAMEOBJECT_ID> ids;
	for (uint i = 0; i < 100; ++i) {
		GAMEOBJECT_ID id = Engine::add_gameobject<StaticObject>().id();
		ids.push_back(id);
	}
	for (int i = 0; i < 50; ++i) {
		Engine::remove_gameobject(ids[i]);
	}


	Engine::add_gameobject<Player>();
}

void MainGame::mainloop() {
	assert(MainGame::m_initialized);
	Engine::start();
}

void MainGame::teardown() {

}

