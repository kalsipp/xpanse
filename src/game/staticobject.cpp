#include "staticobject.hpp"

StaticObject::StaticObject(GAMEOBJECT_ID id):GameObject(id){
	std::string filename = "./media/stat.png";
	add_component<SpriteComponent>();
	get_component<SpriteComponent>()->load_sprite_from_image(filename);
}

StaticObject::~StaticObject(){

}

