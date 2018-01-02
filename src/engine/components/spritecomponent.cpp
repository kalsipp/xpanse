#include "spritecomponent.hpp"

SpriteComponent::SpriteComponent():
	m_sprite(nullptr),
	m_scale(1, 1) {}

void SpriteComponent::load_sprite_from_image(const std::string & path) {
	std::string filename = helpers::get_filename_from_path(path);
	m_sprite = Sprite(GraphicsManager::get_texture(filename));
}
void SpriteComponent::load_sprite_from_image(const std::string & path, const Rect & rect) {
	std::string filename = helpers::get_filename_from_path(path);
	m_sprite = Sprite(GraphicsManager::get_texture(filename), rect.get_sdl_rect());
}
void SpriteComponent::render(GameObject & user) {
	GraphicsManager::render_texture(
	    m_sprite,
	    Vector2D(user.position()),
	    m_scale,
	    m_angle,
	    m_centered,
	    m_flip
	);
}