#include <SDL2/SDL.h>
#include <cassert>
#include "../engine/inputmanager.hpp"

void inputmanager_test() {
		uint testkey = SDL_SCANCODE_K;
		InputManager::set_key(testkey, true);
		bool val = InputManager::get_key(testkey);
		assert(val);
		val = InputManager::get_key_down(testkey);
		assert(val);
		InputManager::read_inputs();
		val = InputManager::get_key(testkey);
		assert(val);
		val = InputManager::get_key_down(testkey);
		assert(!val);
}

int main() {
	inputmanager_test();
}
