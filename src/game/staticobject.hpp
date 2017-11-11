#pragma once
#include "../engine/gameobject.hpp"
#include "../engine/components/spritecomponent.hpp"

class StaticObject:public GameObject {
public:
	StaticObject(GAMEOBJECT_ID id);
	~StaticObject();
private:
};