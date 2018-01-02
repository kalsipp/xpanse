#include "player.hpp"

Player::Player(GAMEOBJECT_ID id):GameObject(id){
	add_component<SpriteComponent>();
	Rect srcrect(0,0,32,32);
	get_component<SpriteComponent>()->load_sprite_from_image(PLAYER_SPRITE_SHEET, srcrect);

	add_component<PlayerController>();
}