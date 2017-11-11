#pragma once
#include <string>
#include <cassert>
#include <SDL2/SDL.h>
#include "vector2d.hpp"

class Sprite {
public:
	Sprite(SDL_Texture * new_text);
	~Sprite();
	SDL_Texture * get_sdl_texture();
private:
	SDL_Texture * m_texture = nullptr;
};