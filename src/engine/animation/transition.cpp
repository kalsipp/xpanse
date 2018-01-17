#include "transition.hpp"

AfterTime::AfterTime(float duration): m_duration(duration) {}

void AfterTime::start() {
	m_timer.start();
}

bool AfterTime::transition() {
	return m_timer.get_elapsed_milliseconds() > m_duration;
}