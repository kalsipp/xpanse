#include "vector3d.hpp"

Vector3D::Vector3D(float _x, float _y, float _z):
	x(_x), y(_y), z(_z) {}

Vector3D & Vector3D::operator+=(const Vector3D & other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
Vector3D & Vector3D::operator-=(const Vector3D & other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

void Vector3D::set(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}


std::ostream & operator <<(std::ostream & stream, const Vector3D & p){
	stream << "(" << p.x << "," << p.y << "," << p.z << ")";
	return stream;
}