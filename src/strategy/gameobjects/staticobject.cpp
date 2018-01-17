#include "staticobject.hpp"

StaticObject::StaticObject(GAMEOBJECT_ID id):GameObject(id){
	add_component<SpriteComponent>();
	get_component<SpriteComponent>().lock()->load_sprite_from_image(DEFAULT_SPRITE);
}

StaticObject::~StaticObject(){

}

