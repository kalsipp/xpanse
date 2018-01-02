#pragma once
#include "../../engine/gameobject.hpp"
#include "../../engine/components/textcomponent.hpp"
#include "../../engine/component.hpp"
#include "../../engine/basics/timer.hpp"


class FPSCounter:public GameObject{
public:
	FPSCounter(GAMEOBJECT_ID);
	void update() final override;
private:
	Timer m_timer;
	uint cycles_per_update = 10;
	uint current_cycle = 0;
};