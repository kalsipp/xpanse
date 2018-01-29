#pragma once
#include <memory>
#include "gameobject.hpp"
class GameObject;
class Component {
public:
	Component();
	virtual void setup (std::weak_ptr<GameObject> user) {m_parent = user;}
	virtual void update(GameObject & user) {(void) user;}
	virtual void render(GameObject & user) {(void) user;}
	virtual void teardown(GameObject & user) {(void) user;}
	virtual ~Component() {}
	bool & enabled();
protected:
	bool m_enabled = true;
	std::weak_ptr<GameObject> m_parent;
};