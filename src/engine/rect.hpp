#pragma once
#include <SDL2/SDL.h>
class Rect {
public:
	Rect(float _x = 0, float _y = 0, float _size_x = 0, float _size_y = 0);
	SDL_Rect get_sdl_rect();
	float x = 0;
	float y = 0;
	float size_x = 0;
	float size_y = 0;
private:
};