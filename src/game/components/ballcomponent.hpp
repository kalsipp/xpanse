#pragma once
#include "../../engine/component.hpp"
#include "../../engine/components/spritecomponent.hpp"

class BallComponent:public Component{
public:
	void setup(std::weak_ptr<GameObject>) final override;
	void update(GameObject & user) final override;
private:
};