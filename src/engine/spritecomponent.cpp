#include "spritecomponent.hpp"

SpriteComponent::SpriteComponent(const std::string & filename) {
	SDL_Surface * new_surf = IMG_Load(filename.c_str());
	assert(new_surf != NULL && "Could not find load spritecomponent");
	m_sprite = new Sprite(new_surf);
	SDL_FreeSurface(new_surf);
	m_scale = Vector2D(1,1);
}

SpriteComponent::~SpriteComponent(){
	delete m_sprite;
}

void SpriteComponent::update(const GameObject & user) {
	GraphicsManager::render_texture(
	    m_sprite->get_sdl_texture(),
	    Vector2D(user.position()),
	    m_scale,
	    m_angle,
	    m_centered,
	    m_flip
	);
}

