#pragma once
#include <SDL2/SDL.h>
#include "component.hpp"
#include "sprite.hpp"
#include "vector2d.hpp"
#include "gameobject.hpp"

class SpriteComponent: public Component {
public:
	SpriteComponent(const std::string & filename);
	~SpriteComponent();
	void update(const GameObject & user) final override;
private:
	Sprite * m_sprite;
	Vector2D m_scale;
	double m_angle = 0;
	bool m_centered = false;
	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
};