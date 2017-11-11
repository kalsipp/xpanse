#include "vector2d.hpp"


Vector2D::Vector2D() {}
Vector2D::Vector2D(float _x, float _y): x(_x), y(_y) {}
Vector2D::Vector2D(const Vector3D & vec): x(vec.x), y(vec.y) {}
void Vector2D::set(float _x, float _y) {
	x = _x;
	y = _y;
}
SDL_Point Vector2D::get_sdl_point() {
	return SDL_Point{int(round(x)), int(round(y))};
}
