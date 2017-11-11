#include "spritecomponent.hpp"

SpriteComponent::SpriteComponent():
	m_sprite(nullptr),
	m_scale(1, 1) {}

void SpriteComponent::load_sprite_from_image(const std::string & filename){
	m_sprite = GraphicsManager::load_sprite_from_image(filename);
}

void SpriteComponent::render(GameObject & user) {
	GraphicsManager::render_texture(
	    m_sprite.get_sdl_texture(),
	    Vector2D(user.position()),
	    m_scale,
	    m_angle,
	    m_centered,
	    m_flip
	);

}