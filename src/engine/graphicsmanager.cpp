#include "graphicsmanager.hpp"

bool GraphicsManager::m_initialized = false;
SDL_Window * GraphicsManager::m_main_window = nullptr;
SDL_Surface * GraphicsManager::m_main_surface = nullptr;
SDL_Renderer * GraphicsManager::m_main_renderer = nullptr;
uint GraphicsManager::m_screen_width = 1024 ;
uint GraphicsManager::m_screen_height = 768;

void GraphicsManager::initialize() {
	if (!GraphicsManager::m_initialized) {
		bool init_ok = true;
		if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			std::cout <<  "SDL could not initialize! SDL_Error: " <<  SDL_GetError() << std::endl;
			init_ok = false;
		}
		else
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
			}
			//Create window
			GraphicsManager::m_main_window = SDL_CreateWindow(
			                                     "Let's go bois",
			                                     SDL_WINDOWPOS_UNDEFINED,
			                                     SDL_WINDOWPOS_UNDEFINED,
			                                     m_screen_width,
			                                     m_screen_height,
			                                     SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
			if ( GraphicsManager::m_main_window == NULL )
			{
				std::cout <<  "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
				init_ok = false;
			} else {
				GraphicsManager::m_main_renderer = SDL_CreateRenderer(
				                                       GraphicsManager::m_main_window,
				                                       -1,
				                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				GraphicsManager::m_main_surface = SDL_GetWindowSurface( GraphicsManager::m_main_window );
				if (GraphicsManager::m_main_surface == NULL) {
					std::cout << "Surface could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
					init_ok = false;
				}
				if (GraphicsManager::m_main_renderer == NULL) {
					std::cout << "Renderer could not be created! SDL Error: " << std::string(SDL_GetError()) << std::endl;
					init_ok = false;
				} else if (init_ok)
				{
					SDL_SetRenderDrawColor(GraphicsManager::m_main_renderer, 0x0, 0x0, 0x0, 0x0);
					int img_flags = IMG_INIT_PNG;
					if (!(IMG_Init(img_flags) & img_flags)) {
						std::cout << "SDL_image could not initialize! SDL_image Error: " << std::string(IMG_GetError()) << std::endl;
						init_ok = false;
					}

					if (TTF_Init() == -1)
					{
						std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << std::string(TTF_GetError()) << std::endl;
						init_ok = false;
					}

				}
			}
		}
		assert(init_ok);
		GraphicsManager::m_initialized = true;
	}
}

void GraphicsManager::teardown() {
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

void GraphicsManager::render_texture(SDL_Texture * texture,
                                     const Vector2D & pos,
                                     const Vector2D & scale,
                                     const double angle,
                                     bool centered,
                                     const SDL_RendererFlip flip) {
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
	    NULL, 								// const SDL_Rect*        srcrect. selects a subpart of the texture.
	    &scalerect, 						// const SDL_Rect*        dstrect
	    angle, 								// const double           angle
	    NULL, 								// const SDL_Point*       center
	    flip);								// const SDL_RendererFlip flip
}

void GraphicsManager::execute_rendering() {
	SDL_RenderPresent(GraphicsManager::m_main_renderer);
}

Sprite GraphicsManager::load_sprite_from_image(const std::string & filename) {
	SDL_Surface * new_surf = GraphicsManager::load_image_to_surface(filename);
	SDL_Texture * new_text = GraphicsManager::convert_surface_to_texture(new_surf);
	SDL_FreeSurface(new_surf);
	return Sprite(new_text);
}

SDL_Texture  * GraphicsManager::convert_surface_to_texture(SDL_Surface* new_surf) {
	return SDL_CreateTextureFromSurface(GraphicsManager::m_main_renderer, new_surf);
}

SDL_Surface * GraphicsManager::load_image_to_surface(const std::string & filename) {
	SDL_Surface * new_surf = IMG_Load(filename.c_str());
	assert(new_surf != NULL && filename.c_str());
	return new_surf;
}