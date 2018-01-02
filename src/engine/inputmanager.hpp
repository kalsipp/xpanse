#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>
#include "basics/timer.hpp"

/* Defines when the user presses window cross
Arbitrary value hopefully not occupied by SDL keys
*/
#define SDLK_QUIT  9999

class InputManager {
public:
	static void initialize();
	static void read_inputs();
	static bool get_key(int key);
	static bool get_key_down(int key);
private:
	InputManager();
	static void set_key(int key, bool value);
	static void reset_keys();
	static void add_text_input(const std::string & new_text);
	static void reset_text_input();
	static void set_mouse(bool value);
	static std::string m_text_input;
	static std::map<int, bool> m_keys_static; //Contains if the key was added frame
	static bool m_initialized;
	static bool m_mouse_state;
	static SDL_Event m_sdl_event;
	static std::map<int, bool> m_keys;

	//Testing only
	friend void inputmanager_test();
};