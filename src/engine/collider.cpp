#include "collider.hpp"

std::vector<std::weak_ptr<Collider>> Collider::m_all_colliders;


void Collider::setup(std::weak_ptr<GameObject> user){
	m_parent = user;
	m_me = m_parent.lock()->get_component<Collider>();
	register_collider(m_me);
}

void Collider::teardown(GameObject & user){
	unregister_collider(m_me);
}

const std::vector<std::weak_ptr<GameObject>> & Collider::get_colliding_objects() {

}

bool Collider::may_collide(const std::weak_ptr<GameObject> & other){
	(void) other;
	return true;
}

void Collider::register_collider(std::weak_ptr<Collider> item) {
	m_all_colliders.push_back(item);
}

void Collider::unregister_collider(std::weak_ptr<Collider> item) {
	auto current = m_all_colliders.begin();
	while (current != m_all_colliders.end()) {
		ASSERT(current->lock(), "Collider is null in unregister");
		if (current->lock() == item.lock()) {
			m_all_colliders.erase(current);
			return;
		}
	}
	ASSERT(false, "Could not unregister collider");
}
