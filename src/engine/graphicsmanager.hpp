#pragma once
#include <cassert>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "vector2d.hpp"
#include "rect.hpp"
class GraphicsManager {

public:
	static void initialize();
	static void teardown();
	static void prepare_rendering();
	static void render_texture(SDL_Texture * texture,
                                     const Vector2D & pos,
                                     const Vector2D & scale,
                                     const double angle,
                                     bool centered,
                                     const SDL_RendererFlip flip);
	static void execute_rendering();
	static SDL_Texture  * convert_surface_to_texture(SDL_Surface*);
private:
	GraphicsManager();
	static bool m_initialized;
	static SDL_Window * m_main_window;
	static SDL_Surface * m_main_surface;
	static SDL_Renderer * m_main_renderer;
	static uint m_screen_width;
	static uint m_screen_height;
};