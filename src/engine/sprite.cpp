#include "sprite.hpp"
Sprite::Sprite(SDL_Surface * new_surf){
	load_image_from_surface(new_surf);
}
void Sprite::load_image_from_surface(SDL_Surface * new_surf) {
	if (m_texture != nullptr) SDL_DestroyTexture(m_texture);
	m_texture = GraphicsManager::convert_surface_to_texture(new_surf);
	assert(m_texture != nullptr && m_texture != NULL);
}

SDL_Texture * Sprite::get_sdl_texture(){
	return m_texture;
}

