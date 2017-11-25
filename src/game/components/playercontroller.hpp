#pragma once
#include "../../engine/component.hpp"
#include "../../engine/inputmanager.hpp"
#include "../image_paths.hpp"
class PlayerController: public Component {
public:
	void update(GameObject & user) final override;
private:
	float m_speed = 1;
};
