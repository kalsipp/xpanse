#pragma once
#include <string>
#include <SDL2/SDL.h>
#include "vector2d.hpp"
#include "helpers.hpp"
class Sprite {
public:
	Sprite(SDL_Texture * new_text, const SDL_Rect &);
	Sprite(SDL_Texture * new_text);
	~Sprite(){}
	SDL_Texture * get_sdl_texture()const;
	void set_sdl_rect(int x = 0, int y = 0, int w = 0, int h = 0);
	const SDL_Rect * get_sdl_rect()const;
private:
	SDL_Texture * m_texture = nullptr;
	SDL_Rect m_rect; 
};