#include "camera.hpp"


std::weak_ptr<Camera> Camera::m_main_camera;

Camera::Camera(GAMEOBJECT_ID id):GameObject(id){
	if(!m_main_camera.lock()){
		m_main_camera = Engine::add_gameobject<Camera>();
	}
}


std::weak_ptr<Camera> Camera::get_main_camera(){
	return m_main_camera;
}