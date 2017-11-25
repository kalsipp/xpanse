#include "gameobject.hpp"

GameObject::GameObject(GAMEOBJECT_ID id): m_id(id) {}

GameObject::~GameObject() {
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		delete (*i);
	}
}

bool & GameObject::enabled() {
	return m_enabled;
}

void GameObject::update() {
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

Vector3D & GameObject::position() {
	return m_position;
}

const Vector3D & GameObject::position()const {
	return m_position;
}

GAMEOBJECT_ID GameObject::id()const {
	return m_id;
}

void GameObject::move(const Vector3D & movement){
	m_position+=movement;
}
void GameObject::set_position(const Vector3D & position){
	m_position = position;
}

