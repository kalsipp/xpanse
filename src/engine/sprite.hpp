#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "graphicsmanager.hpp"
#include "vector2d.hpp"
class Sprite {
public:
	Sprite(SDL_Surface *);
	SDL_Texture * get_sdl_texture();
private:
	void load_image_from_surface(SDL_Surface *);
	SDL_Texture * m_texture = nullptr;
};