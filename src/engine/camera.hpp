#pragma once
#include <memory>
#include "gameobject.hpp"


class Camera: public GameObject {
public:
	Camera(GAMEOBJECT_ID);
	static std::weak_ptr<Camera> get_main_camera();
private:
	static std::weak_ptr<Camera> m_main_camera;
};