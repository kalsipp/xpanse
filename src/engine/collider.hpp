#pragma once
#include <memory>
#include <algorithm>
#include <map>
#include "component.hpp"
class Collider: public Component {
public:
	Collider();
	~Collider();
	virtual void setup(std::weak_ptr<GameObject>) override;
	virtual void teardown(GameObject & user);
	const std::vector<std::weak_ptr<GameObject>> & get_colliding_objects();
protected:
	bool may_collide(const std::weak_ptr<GameObject> &);
	double get_basic_size();
	std::vector<GameObject*> m_colliding_objects;
	static std::vector<std::weak_ptr<Collider>> m_all_colliders;
	std::weak_ptr<Collider> m_me;
private:
	static void register_collider(std::weak_ptr<Collider>);
	static void unregister_collider(std::weak_ptr<Collider>);
};