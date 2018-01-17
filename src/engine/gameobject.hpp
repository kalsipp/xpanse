#pragma once
#include <vector>
#include <string>
#include <memory>
#include "component.hpp"
#include "components/transform.hpp"
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
	std::weak_ptr<component_type> add_component();

	template <class component_type>
	std::weak_ptr<component_type> get_component();

	std::vector<std::shared_ptr<Component>> & get_all_components();

	virtual void update() {}
	void update_components();
	void render();
	void destroy();
	Transform & transform();
	const Transform & transform() const;
	GAMEOBJECT_ID id()const;
	std::string get_name();
protected:
	bool m_enabled = true;
	std::string m_name = "NoName";
	const GAMEOBJECT_ID m_id;
	std::vector<std::shared_ptr<Component>> m_components;
	std::multimap<size_t, std::shared_ptr<Component>> m_component_types;
	Transform m_transform;
};


template <class component_type>
std::weak_ptr<component_type> GameObject::add_component() {
	std::shared_ptr<component_type> new_comp_type = std::make_shared<component_type>();
	m_components.push_back(new_comp_type);
	m_component_types.insert(std::make_pair(typeid(component_type).hash_code(), new_comp_type));
	Logging::log(Logging::TRACE, std::stringstream() << "Adding component " << typeid(component_type).name());
	return new_comp_type;
}

template <class component_type>
std::weak_ptr<component_type> GameObject::get_component() {
	auto iter = m_component_types.find(typeid(component_type).hash_code());
	if(iter != m_component_types.end()){
		return std::static_pointer_cast<component_type>(iter->second);
	}else{
		return std::weak_ptr<component_type>();
	}
	// for (auto i = m_components.begin(); i != m_components.end(); ++i) {
	// 	auto downcastedPtr = std::dynamic_pointer_cast<component_type>(*i);
	// 	if (downcastedPtr)
	// 	{
	// 		return downcastedPtr;
	// 	}
	// }
	// return std::weak_ptr<component_type>();
}
