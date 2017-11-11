#include <random>
#include <chrono>
namespace helpers {

inline uint random_int(int min, int max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

	return dist(rng);

}

}