#pragma once
#include <vector>
#include "component.hpp"
#include "basics/vector3d.hpp"
#include "engine.hpp"

class Component;
class GameObject {
public:
	GameObject(GAMEOBJECT_ID id);
	~GameObject();
	bool & enabled();
	template <class component_type>
	void add_component();
	template <class component_type>
	component_type * get_component();
	void update();
	void render();
	void destroy();
	Vector3D & position();
	const Vector3D & position() const;
	GAMEOBJECT_ID id()const;
protected:
	bool m_enabled = true;
	const GAMEOBJECT_ID m_id;
	std::vector<Component*> m_components;
	Vector3D m_position;
};


template <class component_type>
void GameObject::add_component() {
	Component * new_comp = new component_type();
	m_components.push_back(new_comp);
}

template <class component_type>
component_type * GameObject::get_component() {
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		component_type * component = dynamic_cast<component_type*>(*i);
		if (component != NULL) {
			return component;
		}
	}

	return nullptr;
}
