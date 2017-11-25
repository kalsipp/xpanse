#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "../component.hpp"
#include "../basics/sprite.hpp"
#include "../basics/vector2d.hpp"
#include "../basics/helpers.hpp"
#include "../gameobject.hpp"
#include "../graphicsmanager.hpp"

class SpriteComponent: public Component {
public:
	SpriteComponent();
	void load_sprite_from_image(const std::string &);
	void load_sprite_from_image(const std::string &, const Rect &);
	void render(GameObject & user) final override;
private:
	Sprite m_sprite;
	Vector2D m_scale;
	double m_angle = 0;
	bool m_centered = false;
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
};

