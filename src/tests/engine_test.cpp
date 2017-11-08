#include "../engine/engine.hpp"
#include "../engine/gameobject.hpp"


void basic_add_remove(){
	std::vector<uint> ids;
	int size = 100;
	for (int i = 0; i < size; ++i) {
		GameObject * g = new GameObject();
		uint id = Engine::add_gameobject(g);
		ids.push_back(id);
	}
	for (int i = 0; i < size; ++i) {
		Engine::remove_gameobject(ids[i]);
	}	
}

void add_remove_add(){
	std::vector<uint> ids;
	uint size = 100;
	for (uint i = 0; i < size; ++i) {
		GameObject * g = new GameObject();
		uint id = Engine::add_gameobject(g);
		ids.push_back(id);
	}

	GameObject * g = new GameObject();
	uint id = Engine::add_gameobject(g);
	for(uint i = 0; i < size; ++i){
		assert(id != ids[i]);
	}
}



void engine_test(){
	basic_add_remove();
	add_remove_add();
	Engine::update_gameobjects();
	Engine::render_gameobjects();
	
}
int main() {
	engine_test();
}