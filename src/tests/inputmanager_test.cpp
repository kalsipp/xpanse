#include <SDL2/SDL.h>
#include <cassert>
#include "../engine/inputmanager.hpp"

void inputmanager_test() {
		InputManager::set_key(SDLK_k, true);
		bool val = InputManager::get_key(SDLK_k);
		assert(val);
		val = InputManager::get_key_down(SDLK_k);
		assert(val);
		InputManager::read_inputs();
		val = InputManager::get_key(SDLK_k);
		assert(val);
		val = InputManager::get_key_down(SDLK_k);
		assert(!val);
}

int main() {
	inputmanager_test();
}
