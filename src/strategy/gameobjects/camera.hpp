#pragma once	
#include "../../engine/gameobject.hpp"


class Camera:public GameObject{
public:
	Camera(GAMEOBJECT_ID);
	virtual void update() final override;
private:
	float m_speed = 1;
};