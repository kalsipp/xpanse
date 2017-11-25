#pragma once
#include "../engine/gameobject.hpp"
#include "../engine/components/spritecomponent.hpp"
#include "image_paths.hpp"

class StaticObject:public GameObject {
public:
	StaticObject(GAMEOBJECT_ID id);
	~StaticObject();
private:
};