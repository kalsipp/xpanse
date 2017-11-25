#pragma once
#include <SDL2/SDL.h>
class Rect {
public:
	Rect(
	    float _x = 0,
	    float _y = 0,
	    float _w = 0,
	    float _h = 0);
	SDL_Rect get_sdl_rect()const;
	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Vector2D &);
private:
};