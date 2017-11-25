#include "helpers.hpp"
namespace helpers {

uint random_int(int min, int max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

void nice_assert(bool test, const std::string & info){
	if(!test){
		std::cerr << "Error: " << info << std::endl;	
		assert(test);
	}
}

std::string get_filename_from_path(const std::string & path) {
	std::size_t found = path.find_last_of("/\\");
	if (found == std::string::npos) {
		return "";
	} else {
		return path.substr(found + 1);
	}
}

}