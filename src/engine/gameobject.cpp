#include "gameobject.hpp"

GameObject::GameObject(GAMEOBJECT_ID id): m_id(id){
}

GameObject::~GameObject() {
	m_components.clear();
}

bool & GameObject::enabled() {
	return m_enabled;
}

std::vector<std::shared_ptr<Component>> & GameObject::get_all_components(){
	return m_components;
}

void GameObject::update_components() {
	if (!m_enabled) return;
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		(*i)->update(*this);
	}
}

void GameObject::render() {
	if (!m_enabled) return;
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		(*i)->render(*this);
	}

}

void GameObject::destroy() {
	Engine::remove_gameobject(m_id);
}

Transform & GameObject::transform(){
	return m_transform;
}
const Transform & GameObject::transform() const{
	return m_transform;
}

GAMEOBJECT_ID GameObject::id()const {
	return m_id;
}
std::string GameObject::get_name() {
	return m_name;
}
