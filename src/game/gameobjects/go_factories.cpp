#include "go_factories.hpp"

std::weak_ptr<GameObject> add_ball(){
	auto newobj = Engine::add_gameobject<GameObject>();
	newobj.lock()->add_component<BallComponent>();
	newobj.lock()->add_component<SpriteComponent>();
	return newobj;
}