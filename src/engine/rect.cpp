#include "rect.hpp"

Rect::Rect(float _x, float _y, float _size_x, float _size_y):
	x(_x), y(_y), size_x(_size_x), size_y(_size_y) {}

SDL_Rect Rect::get_sdl_rect() {
	return SDL_Rect{int(round(x)), int(round(y)), int(round(size_x)), int(round(size_y))};
}
