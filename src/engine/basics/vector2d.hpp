#pragma once
#include <SDL2/SDL.h>
#include "vector3d.hpp"
class Vector3D;
class Vector2D {
public:
	Vector2D();
	Vector2D(float x, float y=0);
	Vector2D(const Vector3D &);
	operator Vector3D();
	void set(float, float);
	SDL_Point get_sdl_point();
	float x = 0;
	float y = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Vector2D &);
private:

};