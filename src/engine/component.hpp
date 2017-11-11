#pragma once
#include "gameobject.hpp"
class GameObject;
class Component {
public:
	virtual void update(GameObject & user){(void) user;}
	virtual void render(GameObject & user){(void) user;}
	virtual ~Component(){}
	bool & enabled();
private:
	bool m_enabled = true;
};