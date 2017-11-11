#include "sprite.hpp"

Sprite::Sprite(SDL_Texture * new_text) {
	m_texture = new_text;
}

Sprite::~Sprite() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
	}
}

SDL_Texture * Sprite::get_sdl_texture() {
	return m_texture;
}

