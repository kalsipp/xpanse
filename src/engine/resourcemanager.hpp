#pragma once
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "basics/resourcefile.hpp"
#include "basics/logging.hpp"
#include "../../external_libs/libzippp/src/libzippp.h"

/* Class to abstract access to the filesystem */

class ResourceManager {
public:
	static void set_source_file(const std::string &);
	static void add_item(SDL_RWops*);
	static ResourceFile * get_item(const std::string & name);
	static void free_item(ResourceFile*);
private:
	static ResourceFile * get_engine_item(const std::string & name);
	static ResourceFile * get_game_item(const std::string & name);
	static bool is_src_engine(std::string &);
	static ResourceFile * load_item(const std::string source, const std::string & name);
	static const std::string m_engine_zip_path;
	static std::string m_source_zip_path;
};