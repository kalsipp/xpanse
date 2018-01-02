#pragma once
#include "../engine.hpp"
struct Debug_CloseGameComponent : public Component {
	inline void update(GameObject & user) final override {
		(void)user;
		if (InputManager::get_key_down(SDLK_QUIT) ||
		        InputManager::get_key_down(SDL_SCANCODE_Q)) {
			Engine::stop();
		}
	}
};