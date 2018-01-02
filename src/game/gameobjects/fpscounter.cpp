#include "fpscounter.hpp"

FPSCounter::FPSCounter(GAMEOBJECT_ID id): GameObject(id) {
	TextComponent * t = add_component<TextComponent>();
	t->set_text("FPS: 0");
	t->set_font_size(72);

}

void FPSCounter::update() {
	current_cycle++;
	if (current_cycle % cycles_per_update == 0) {
		double ms = m_timer.get_elapsed_milliseconds();
		ms /= 1000;
		int fps = int( cycles_per_update / ms);
		get_component<TextComponent>()->set_text("FPS: " + std::to_string(fps));
		m_timer.start();
	}
}