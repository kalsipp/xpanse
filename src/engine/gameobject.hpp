#pragma once
#include <vector>
#include "component.hpp"
#include "vector3d.hpp"
class GameObject {
public:
	virtual ~GameObject();
	virtual void update();
	virtual void render();
	Vector3D & position();
	const Vector3D & position() const;
protected:
	std::vector<Component*> m_components;
	Vector3D m_position;
};