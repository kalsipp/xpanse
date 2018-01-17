#include "playercontroller.hpp"

void PlayerController::update(GameObject & user) {
	if (InputManager::get_key(SDL_SCANCODE_W)) {
		user.transform().move(Vector3D(0, -m_speed, 0));
	}
	if (InputManager::get_key(SDL_SCANCODE_A)) {
		user.transform().move(Vector3D(-m_speed, 0, 0));
	}
	if (InputManager::get_key(SDL_SCANCODE_S)) {
		user.transform().move(Vector3D(0, m_speed, 0));
	}
	if (InputManager::get_key(SDL_SCANCODE_D)) {
		user.transform().move(Vector3D(m_speed, 0, 0));
	}


}