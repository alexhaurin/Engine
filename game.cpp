#include "game.h"

Game::Game() {

}

void Game::Run() {
	
	int counter = 1;
	while (1) {
		auto startTime = std::chrono::system_clock::now();
		Update(1.0);
		Draw();
		HandleEvents();
		auto endTime = std::chrono::system_clock::now();

		//Seconds between updates
		deltaTime = std::chrono::duration<double, std::milli>(endTime - startTime).count() / 1000;

		int x = (1000 / 60) - deltaTime;

		//Test
		std::cout << counter << std::endl;
		counter++;

		std::this_thread::sleep_for(std::chrono::milliseconds(x));
	}
}

void Game::Update(double dt) {

}

void Game::Draw() {

}

void Game::HandleEvents() {

}
