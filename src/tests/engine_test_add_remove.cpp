#include <time.h>
#include <stdlib.h>
#include <thread>
#include <typeinfo>
#include "../engine/engine.hpp"
#include "../engine/basics/timer.hpp"
#include "../engine/gameobject.hpp"
#include "../engine/basics/helpers.hpp"

void pls_no_optimization() {}
void stopper() {
	Timer t;
	t.start();
	int duration = 1; //seconds
	while (t.get_elapsed_seconds() < duration) {
		pls_no_optimization();
	}
	Engine::stop();
}

struct Destroy_Self: public Component {
	Destroy_Self() {
	}
	void update(GameObject & user) override {
		user.destroy();
	}
};

struct Spawn_SelfDestroyer: public Component {
	Spawn_SelfDestroyer() {
		m_counter = helpers::random_int(1, 10);
	}
	void update(GameObject & user) override {
		if (m_counter) {
			m_counter--;
			std::weak_ptr<GameObject> p = Engine::add_gameobject<GameObject>();
			p.lock()->add_component<Destroy_Self>();
		} else {
			user.destroy();
		}
	}
	int m_counter = 0;
};

void create_many_objects() {
	Engine::initialize();
	for (int i = 0; i < 1000; ++i) {
		std::weak_ptr<GameObject> p = Engine::add_gameobject<GameObject>();
		p.lock()->add_component<Spawn_SelfDestroyer>();
	}
	std::thread t = std::thread(stopper);
	Engine::start();
	t.join();
}


void dynamic_cast_gameobject() {
	/*
		Test to confirm the usage of shared pointers that have
		been dynamically cast.
	*/
	// struct ExpObj: public GameObject
	// {
	// 	ExpObj(GAMEOBJECT_ID id): GameObject(id) {}
	// };

	// struct BaseObj
	// {
	// 	int x = 0;
	// };
	// struct  ChildObj: public BaseObj
	// {
	// 	ChildObj() {x = 3;}
	// };
	// {
	// 	std::weak_ptr<GameObject> wp = Engine::add_gameobject<ExpObj>();
	// 	Engine::put_gameobjects_into_world();
	// 	GAMEOBJECT_ID i = wp.lock()->id();
	// 	{
	// 		std::weak_ptr<ExpObj> sp = Engine::get_gameobject<ExpObj>(i);
	// 		std::weak_ptr<GameObject> wp2 = Engine::get_gameobject(i);
	// 		std::cout << wp.lock()->transform().get_position() << std::endl;
	// 		std::cout << sp.lock()->transform().get_position() << std::endl;
	// 		std::cout << wp.lock()->transform().get_position() << std::endl;
	// 		std::cout << wp.lock().use_count() << std::endl;
	// 		assert(wp.lock().use_count() == 4);
	// 		assert(wp.lock().get() == sp.lock().get());
	// 		assert(wp2.lock().get() == sp.lock().get());
	// 	}
	// 	assert(wp.lock());
	// 	assert(wp.lock().use_count() == 2);
	// 	Engine::remove_gameobject(i);
	// 	Engine::remove_gameobject_from_world();
	// }

	{
		// struct X
		// {
		// 	static std::weak_ptr<ChildObj> cast_to_weak(std::weak_ptr<BaseObj> & bo) {
		// 		std::weak_ptr<ChildObj> spco = std::static_pointer_cast<ChildObj>(bo);
		// 		return spco;
		// 	}

		// };
		// std::weak_ptr<BaseObj> spbo = std::make_shared<BaseObj> ();


		// std::weak_ptr<ChildObj> wpco = X::cast_to_weak(spbo);
		// std::cout << "Testing casted weak_ptr"  <<wpco.lock()->x << std::endl;
		// int i = 10;
		// int j = 420;
		// float k = 20010;
		// std::cout << typeid(i).hash_code() << std::endl;
		// std::cout << typeid(j).hash_code() << std::endl;
		// std::cout << typeid(k).hash_code() << std::endl;

	}

}



int main() {
	create_many_objects();
	dynamic_cast_gameobject();
	return 0;
}
