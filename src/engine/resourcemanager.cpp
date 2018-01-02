#include "resourcemanager.hpp"

using namespace libzippp;
const std::string ResourceManager::m_engine_zip_path = "engine.zip";
std::string ResourceManager::m_source_zip_path = "";

void ResourceManager::set_source_file(const std::string & path) {
	m_source_zip_path = path;
	ZipArchive zf(path);
	bool result = zf.open(ZipArchive::READ_ONLY);
	ASSERT(result, "Could not open resource zip " + path);
	zf.close();
}

void ResourceManager::add_item(SDL_RWops* item) {
	(void)item;
	//do nothing
	//should you even be able to add a resource item?
	ASSERT(false, "Need to add the add_item function");
}

ResourceFile * ResourceManager::get_engine_item(const std::string & name) {
	return ResourceManager::load_item(m_engine_zip_path, name);
}

ResourceFile * ResourceManager::get_game_item(const std::string & name) {
	ASSERT(m_source_zip_path != "", "You must load game zip first");
	return ResourceManager::load_item(m_source_zip_path, name);
}

ResourceFile * ResourceManager::get_item(const std::string & name) {
	std::string path = name;
	if (is_src_engine(path)) {
		return get_engine_item(path);
	} else {
		return get_game_item(path);
	}
}

void ResourceManager::free_item(ResourceFile * item) {
	delete item;
}

bool ResourceManager::is_src_engine(std::string & path) {
	/* To separate engine items, their paths are defined as ENGINE<path> */
	std::string engine_str = "ENGINE";
	if (path.length() >= engine_str.length()) {
		if (path.substr(0, engine_str.length()) == engine_str) {
			path = path.substr(engine_str.length(), path.length());
			return true;
		}
	}
	return false;
}

ResourceFile * ResourceManager::load_item(const std::string source, const std::string & name) {
	Logging::log(Logging::INFO, std::stringstream() << "Loading file " << name);
	ZipArchive zf(source);
	bool result = zf.open(ZipArchive::READ_ONLY);
	ASSERT(result, "Could not open base zip " + source);
	ZipEntry zentry = zf.getEntry(name);
	ASSERT(!zentry.isNull() and zentry.getSize(), "Could not open file " + name + " from source " + source);
	void * pentry = zentry.readAsBinary();
	ResourceFile * f = new ResourceFile(pentry, zentry.getSize());
	zf.close();
	return f;

}
