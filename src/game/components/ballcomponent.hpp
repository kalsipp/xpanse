#pragma once
#include "../../engine/component.hpp"
#include "../../engine/components/spritecomponent.hpp"

class BallComponent:public Component{
public:
	void setup(GameObject & user) final override;
	void update(GameObject & user) final override;
private:
};