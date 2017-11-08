#include "maingame.hpp"



int main() {
	MainGame::initialize();
	MainGame::mainloop();
	MainGame::teardown();
}