#include "graphicsmanager.hpp"

/* Parameters */

bool GraphicsManager::m_initialized = false;
SDL_Window * GraphicsManager::m_main_window = nullptr;
SDL_Surface * GraphicsManager::m_main_surface = nullptr;
SDL_Renderer * GraphicsManager::m_main_renderer = nullptr;
uint GraphicsManager::m_screen_width = 1024 ;
uint GraphicsManager::m_screen_height = 768;
std::map<std::string, SDL_Texture*> GraphicsManager::m_textures;

/* Public Routines */

void GraphicsManager::initialize() {
	assert(!GraphicsManager::m_initialized);
	int ok = SDL_Init(SDL_INIT_VIDEO);
	ASSERT(ok >= 0,
	       "SDL could not initialize! SDL_Error: " +  std::string(SDL_GetError()));
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	GraphicsManager::m_main_window = SDL_CreateWindow(
	                                     "Let's go bois",
	                                     SDL_WINDOWPOS_UNDEFINED,
	                                     SDL_WINDOWPOS_UNDEFINED,
	                                     m_screen_width,
	                                     m_screen_height,
	                                     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	ASSERT(GraphicsManager::m_main_window != NULL,
	       "Window could not be created! SDL_Error:" + std::string(SDL_GetError()));
	GraphicsManager::m_main_renderer = SDL_CreateRenderer(
	                                       GraphicsManager::m_main_window,
	                                       -1,
	                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	ASSERT(GraphicsManager::m_main_renderer != NULL,
	       "Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));
	GraphicsManager::m_main_surface = SDL_GetWindowSurface( GraphicsManager::m_main_window );
	ASSERT(GraphicsManager::m_main_surface != NULL,
	       "Surface could not be created! SDL Error: " + std::string(SDL_GetError()));
	SDL_SetRenderDrawColor(GraphicsManager::m_main_renderer, 0x0, 0x0, 0x0, 0x0);

	int img_flags = IMG_INIT_PNG;
	ok = IMG_Init(img_flags) & img_flags;
	ASSERT(ok,
	       "SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()));

	ok = TTF_Init();
	ASSERT(ok != -1,
	       "SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
	GraphicsManager::m_initialized = true;
}

void GraphicsManager::teardown() {
	for (auto i = GraphicsManager::m_textures.begin(); i != GraphicsManager::m_textures.end(); ++i) {
		SDL_DestroyTexture((*i).second);
	}
	SDL_DestroyRenderer(GraphicsManager::m_main_renderer);
	SDL_FreeSurface(GraphicsManager::m_main_surface);
	SDL_DestroyWindow(GraphicsManager::m_main_window );
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

void GraphicsManager::prepare_rendering() {
	SDL_SetRenderDrawColor(GraphicsManager::m_main_renderer, 0, 0, 0, 1);
	SDL_RenderClear(GraphicsManager::m_main_renderer);
}

void GraphicsManager::render_texture(const Sprite & sprite,
                                     const Vector2D & pos,
                                     const Vector2D & scale,
                                     const double angle,
                                     bool centered,
                                     const SDL_RendererFlip flip) {
	SDL_Texture * texture = sprite.get_sdl_texture();
	assert(texture != nullptr && texture != NULL);
	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	float posx = 0;
	float posy = 0;
	float scalex = width * scale.x;
	float scaley = height * scale.y;
	if (centered) {
		posx = round(pos.x - scalex / 2);
		posy = round(pos.y - scaley / 2);
	} else {
		posx = round(pos.x);
		posy = round(pos.y);
	}
	SDL_Rect scalerect = {int(round(posx)),
	                      int(round(posy)),
	                      int(round(scalex)),
	                      int(round(scaley))
	                     };
	
	SDL_RenderCopyEx(
	    GraphicsManager::m_main_renderer,  	// SDL_Renderer*          renderer
	    texture, 							// SDL_Texture*           texture
	    sprite.get_sdl_rect(), 								// const SDL_Rect*        srcrect. selects a subpart of the texture.
	    &scalerect, 						// const SDL_Rect*        dstrect
	    angle, 								// const double           angle
	    NULL, 								// const SDL_Point*       center
	    flip);								// const SDL_RendererFlip flip
}

void GraphicsManager::execute_rendering() {
	SDL_RenderPresent(GraphicsManager::m_main_renderer);
}

void GraphicsManager::load_texture(const std::string & path) {
	SDL_Surface * new_surf = GraphicsManager::load_image_to_surface(path);
	SDL_Texture * new_text = GraphicsManager::convert_surface_to_texture(new_surf);
	SDL_FreeSurface(new_surf);
	std::string filename = helpers::get_filename_from_path(path);
	assert(!m_textures.count(filename));
	m_textures[filename] = new_text;
}

SDL_Texture * GraphicsManager::get_texture(const std::string & filename) {
	auto it = GraphicsManager::m_textures.find(filename);
	ASSERT(it != GraphicsManager::m_textures.end(), "Has not loaded " + filename);
	return (*it).second;
}

/* Private routines */

SDL_Surface * GraphicsManager::load_image_to_surface(const std::string & filename) {
	SDL_Surface * new_surf = IMG_Load(filename.c_str());
	ASSERT(new_surf, IMG_GetError());
	return new_surf;
}

SDL_Texture  * GraphicsManager::convert_surface_to_texture(SDL_Surface* new_surf) {
	return SDL_CreateTextureFromSurface(GraphicsManager::m_main_renderer, new_surf);
}
