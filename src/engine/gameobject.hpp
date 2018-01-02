#pragma once
#include <vector>
#include <string>

#include "component.hpp"
#include "basics/vector3d.hpp"
#include "basics/logging.hpp"
#include "engine.hpp"


class Component;
class GameObject {
public:
	GameObject(GAMEOBJECT_ID id);
	virtual ~GameObject();
	bool & enabled();

	template <class component_type>
	component_type * add_component();

	template <class component_type>
	component_type * get_component();

	virtual void update() {}
	void update_components();
	void render();
	void destroy();
	Vector3D & position();
	const Vector3D & position() const;
	GAMEOBJECT_ID id()const;
	void move(const Vector3D &);
	void set_position(const Vector3D &);
	std::string get_name();
protected:
	bool m_enabled = true;
	std::string m_name = "NoName";
	const GAMEOBJECT_ID m_id;
	std::vector<Component*> m_components;
	Vector3D m_position;
};


template <class component_type>
component_type * GameObject::add_component() {
	component_type * new_comp_type = new component_type();
	Component * new_comp = new_comp_type;
	m_components.push_back(new_comp);
	Logging::log(Logging::TRACE, std::stringstream()<<"Adding component " << typeid(component_type).name());
	return new_comp_type;
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
