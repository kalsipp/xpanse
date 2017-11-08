#pragma once
#include "../engine/gameobject.hpp"
#include "../engine/spritecomponent.hpp"

class StaticObject:public GameObject {
public:
	StaticObject();
	~StaticObject();
	void render() final override;
private:
};