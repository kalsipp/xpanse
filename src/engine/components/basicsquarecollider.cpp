#include "basicsquarecollider.hpp"

BasicSquareCollider::BasicSquareCollider(const Vector2D & size): m_size(size) 
{}

void BasicSquareCollider::update(GameObject & user) {

}

std::vector<std::weak_ptr<GameObject>> get_colliding_objects() {

}