#include <time.h>
#include <stdlib.h>
#include <thread>
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
			Engine::add_gameobject<GameObject>().add_component<Destroy_Self>();
		} else {
			user.destroy();
		}
	}
	int m_counter = 0;
};


int main() {
	Engine::initialize();
	for (int i = 0; i < 1000; ++i) {
		Engine::add_gameobject<GameObject>().add_component<Spawn_SelfDestroyer>();
	}
	std::thread t = std::thread(stopper);
	Engine::start();
	t.join();

}
