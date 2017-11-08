#include "gameobject.hpp"


GameObject::~GameObject() {
	for (auto i = m_components.begin(); i != m_components.end(); ++i) {
		delete (*i);
	}
}

void GameObject::update() {

}

void GameObject::render() {

}

Vector3D & GameObject::position(){
	return m_position;
}

const Vector3D & GameObject::position()const {
	return m_position;
}