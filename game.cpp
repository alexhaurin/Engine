#include "game.h"

Game::Game() {

	auto window = std::make_shared<sf::Window>();

	std::cout << "Created" << std::endl;
}

Game::~Game() {

	std::cout << "Destroyed" << std::endl;

}

void Game::Run() {

	auto targetTime = std::chrono::milliseconds(1000 / 60);
	while (1) {
		auto startTime = std::chrono::high_resolution_clock::now();
		HandleEvents();
		Update(1.0);
		Draw();
		auto endTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = startTime - endTime;


		if (deltaTime < targetTime) {

			auto remainingTime = targetTime - deltaTime - std::chrono::milliseconds(3);
			if (remainingTime > std::chrono::milliseconds(0)) {
				std::this_thread::sleep_for(remainingTime);

				while ((std::chrono::high_resolution_clock::now() - startTime) < targetTime) {}
			}
		}

		std::cout << std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000 << std::endl;



	}
}

void Game::HandleEvents() {

}

void Game::Update(double dt) {

}

void Game::Draw() {

}
