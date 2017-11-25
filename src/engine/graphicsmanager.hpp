#pragma once
#include <cassert>
#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "basics/vector2d.hpp"
#include "basics/rect.hpp"
#include "basics/sprite.hpp"
#include "basics/helpers.hpp"
class GraphicsManager {
public:
	static void initialize();
	static void teardown();
	static void prepare_rendering();
	static void render_texture(const Sprite &,
	                           const Vector2D & pos,
	                           const Vector2D & scale,
	                           const double angle,
	                           bool centered,
	                           const SDL_RendererFlip flip);
	static void execute_rendering();
	static void load_texture(const std::string & path);
	static SDL_Texture * get_texture(const std::string & filename);
private:
	static SDL_Surface * load_image_to_surface(const std::string & path);
	static SDL_Texture * convert_surface_to_texture(SDL_Surface*);
	GraphicsManager();
	static bool m_initialized;
	static std::map<std::string, SDL_Texture*> m_textures;
	static SDL_Window * m_main_window;
	static SDL_Surface * m_main_surface;
	static SDL_Renderer * m_main_renderer;
	static uint m_screen_width;
	static uint m_screen_height;
};