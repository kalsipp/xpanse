#include "maingame.hpp"
#include <unistd.h>

bool MainGame::m_initialized = false;
bool MainGame::m_running = false;

void MainGame::initialize() {
	if (!MainGame::m_initialized) {
		MainGame::m_initialized = true;
		MainGame::m_running = true;
		Engine::initialize();
	}

	std::vector<int> ids; 
	for(uint i = 0; i < 100; ++i){
		GameObject * g = new StaticObject();
		ids.push_back(Engine::add_gameobject(g));
	}
	for(int i = 0; i < 50; ++i){
		Engine::remove_gameobject(ids[i]);
	}
}

void MainGame::mainloop() {
	Engine::start();
	while (true) {
		if (InputManager::get_key(SDLK_QUIT)) {
			Engine::stop();
			break;
		}
	}
}

void MainGame::teardown() {

}

