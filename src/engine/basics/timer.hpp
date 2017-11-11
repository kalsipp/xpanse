#pragma once
#include <chrono>
class Timer{
public:
	void start();
	double get_elapsed_microseconds();
	double get_elapsed_milliseconds();
	double get_elapsed_seconds();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
	std::chrono::high_resolution_clock m_clock;
};