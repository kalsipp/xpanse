#include "inputmanager.hpp"

/*Params*/

bool InputManager::m_initialized = false;
std::string InputManager::m_text_input = "";
// std::map<int, bool> InputManager::m_keys;
std::map<int, bool> InputManager::m_keys_static;
bool InputManager::m_mouse_state = false;
SDL_Event InputManager::m_sdl_event;
std::map<int, bool> InputManager::m_keys;
/*Publics*/

void InputManager::initialize() {
	if (!InputManager::m_initialized) {
		InputManager::m_initialized = true;
	}
}

void InputManager::read_inputs() {
	InputManager::reset_keys();
	InputManager::reset_text_input();

	while (SDL_PollEvent(&InputManager::m_sdl_event) != 0) {
		switch (InputManager::m_sdl_event.type) {

		//If the window cross is pressed.
		case SDL_QUIT:
			InputManager::set_key(SDLK_QUIT, true);
			break;
		//If continuous text if being added
		case SDL_TEXTINPUT:
			InputManager::add_text_input(InputManager::m_sdl_event.text.text);
			break;
		//On key up
		case SDL_KEYUP:
			InputManager::set_key(InputManager::m_sdl_event.key.keysym.scancode, false);
			break;
		//On key down
		case SDL_KEYDOWN:
			if (!InputManager::m_sdl_event.key.repeat) {
				InputManager::set_key(InputManager::m_sdl_event.key.keysym.scancode, true);
			}
			break;
		//On mouse up
		case SDL_MOUSEBUTTONDOWN:
			InputManager::set_mouse(true);
			break;
		//On mouse down
		case SDL_MOUSEBUTTONUP:
			InputManager::set_mouse(false);
			break;
		}
	}

}

bool InputManager::get_key(int key) {
	if(!m_keys.count(key)) return false;
	return m_keys[key];
}
bool InputManager::get_key_down(int key) {
	if (InputManager::m_keys_static.count(key) == 0) return false;
	return InputManager::m_keys_static[key];
}

/*Privates*/

void InputManager::set_key(int key, bool val) {
	InputManager::m_keys[key] = val;
	if(val)	InputManager::m_keys_static[key] = val;
}

void InputManager::reset_keys() {
	InputManager::m_keys_static.clear();
}

void InputManager::add_text_input(const std::string & text) {
	InputManager::m_text_input += text;
}

void InputManager::reset_text_input() {
	InputManager::m_text_input = "";
}

void InputManager::set_mouse(bool val) {
	InputManager::m_mouse_state = val;
}