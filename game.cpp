#include "game.h"

Game::Game() {

}

void Game::Run() {
	
	while (1) {
		auto startTime = std::chrono::system_clock::now();
		Update(1.0);
		Draw();
		HandleEvents();
		auto endTime = std::chrono::system_clock::now();
		double deltaTime = std::chrono::duration<double>(endTime - startTime).count();
		std::cout << deltaTime << std::endl;
	}
}

void Game::Update(double dt) {

}

void Game::Draw() {

}

void Game::HandleEvents() {

}