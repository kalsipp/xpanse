#include "textcomponent.hpp"

TextComponent::TextComponent(): m_sprite(nullptr) {
	ResourceFile* fontfile =  ResourceManager::get_item(DEFAULT_FONT);
	m_font = fontfile->get_font(default_font_size);
	ResourceManager::free_item(fontfile);
	ASSERT(m_font, "Could not load font " + std::string(DEFAULT_FONT));
	m_font_source = DEFAULT_FONT;
	m_sprite = Sprite(GraphicsManager::get_texture_from_text("", m_font, m_color));
}

TextComponent::~TextComponent() {
	if (m_font != nullptr) TTF_CloseFont(m_font);
}

void TextComponent::set_font_size(int size) {
	if (m_font != nullptr) TTF_CloseFont(m_font);
	ResourceFile * fontfile =  ResourceManager::get_item(m_font_source);
	m_font = fontfile->get_font(size);
	ResourceManager::free_item(fontfile);
	ASSERT(m_font, "Could not load font " + m_font_source);
	set_text(m_text);
}

std::string TextComponent::get_text() {
	return m_text;
}

void TextComponent::set_text(const std::string & text) {
	m_text = text;
	m_sprite = Sprite(GraphicsManager::get_texture_from_text(m_text, m_font, m_color));
	ASSERT(m_sprite.get_sdl_texture(), "Could not set text " + std::string(SDL_GetError()));
}

void TextComponent::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	m_color = {r, g, b, a};
}

void TextComponent::render(GameObject & user) {
	ASSERT(m_sprite.get_sdl_texture(), "This is apparently zero now");
	GraphicsManager::render_texture(
	    m_sprite,
	    Vector2D(user.transform().get_position()),
	    m_scale,
	    m_angle,
	    m_centered,
	    m_flip
	);
}