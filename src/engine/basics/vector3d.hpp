#pragma once
#include "vector2d.hpp"
class Vector2D;

class Vector3D {
public:
	Vector3D() {}
	Vector3D(float _x, float _y = 0, float _z = 0);
	Vector3D & operator+=(const Vector3D &);
	Vector3D & operator-=(const Vector3D &);
	void set(float _x, float _y = 0, float _z = 0);
	float x = 0;
	float y = 0;
	float z = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Vector3D &);
private:
};