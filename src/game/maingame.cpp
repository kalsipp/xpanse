#include "maingame.hpp"

bool MainGame::m_initialized = false;

void MainGame::initialize() {
	if (!MainGame::m_initialized) {
		MainGame::m_initialized = true;
		Engine::initialize();
		ResourceManager::set_source_file("game.zip");
		GraphicsManager::load_texture(DEFAULT_SPRITE);
		GraphicsManager::load_texture(PLAYER_SPRITE_SHEET);

		Engine::register_scene("mainscene", myscene);
		Engine::load_scene("mainscene");
	}	
}
void MainGame::mainloop() {
	ASSERT(MainGame::m_initialized, "You need to initialize MainGame");
	Engine::start();
}

void MainGame::teardown() {
	Engine::teardown();
}

