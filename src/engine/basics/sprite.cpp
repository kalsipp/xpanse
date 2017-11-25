#include "sprite.hpp"

Sprite::Sprite(SDL_Texture * new_text): m_texture(new_text) {
	int width = 0;
	int height = 0;
	SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);
	m_rect = {0,0,width, height};

}

Sprite::Sprite(SDL_Texture * new_text, const SDL_Rect & new_rect):
	m_texture(new_text),
	m_rect(new_rect) {
	ASSERT(new_text != nullptr, "Sprite loaded with null texture");
}

SDL_Texture * Sprite::get_sdl_texture()const{
	return m_texture;
}

const SDL_Rect * Sprite::get_sdl_rect() const{
	return &m_rect;
}