#include "staticobject.hpp"

StaticObject::StaticObject(GAMEOBJECT_ID id):GameObject(id){
	add_component<SpriteComponent>();
	get_component<SpriteComponent>()->load_sprite_from_image(DEBUG_SMILEY);
}

StaticObject::~StaticObject(){

}

