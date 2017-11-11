#include <time.h>
#include <stdlib.h>
#include <thread>
#include "../engine/engine.hpp"
#include "../engine/basics/timer.hpp"
#include "../engine/gameobject.hpp"
#include "../engine/basics/helpers.cpp"

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

struct Destroy_Test_SelfDestroyer: public Component {
	Destroy_Test_SelfDestroyer() {
	}
	void update(GameObject & user) override {
		user.destroy();
	}
};

struct Test_SelfDestroyer: public GameObject {
	Test_SelfDestroyer(GAMEOBJECT_ID id):GameObject(id) {
		add_component<Destroy_Test_SelfDestroyer>();
	}
};

struct Spawn_Test_SelfDestroyer: public Component {
	Spawn_Test_SelfDestroyer() {
		m_counter = helpers::random_int(1, 10);
	}
	void update(GameObject & user) override {
		if (m_counter) {
			m_counter--;
			Engine::add_gameobject<Test_SelfDestroyer>();
		} else {
			user.destroy();
		}
	}
	int m_counter = 0;
};



struct Test_DestroyerSpawner: public GameObject {
	Test_DestroyerSpawner(GAMEOBJECT_ID id):GameObject(id) {
		add_component<Spawn_Test_SelfDestroyer>();
	}
};



int main() {
	Engine::initialize();
	for (int i = 0; i < 1000; ++i) {
		Engine::add_gameobject<Test_DestroyerSpawner>();
	}
	std::thread t = std::thread(stopper);
	Engine::start();
	t.join();

}
