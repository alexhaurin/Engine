#include "game.h"

Game::Game()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 800), "Engine2");

	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile("/Users/Alex Haurin/Downloads/HD_Hoopla_Fish.jpg")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sf::Sprite hoopla;
	hoopla.setTexture(*texture);

	std::cout << "Created" << std::endl;
}

Game::~Game()
{
	std::cout << "Destroyed" << std::endl;
}

void Game::Run()
{
	auto targetTime = std::chrono::milliseconds(1000 / 60);
	while (window->isOpen()) {
		auto startTime = std::chrono::high_resolution_clock::now();
		HandleEvents();
		Update(1.0);
		Draw();
		auto endTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = startTime - endTime;


		if (deltaTime < targetTime)
		{
			auto remainingTime = targetTime - deltaTime - std::chrono::milliseconds(3);
			if (remainingTime > std::chrono::milliseconds(0))
			{
				std::this_thread::sleep_for(remainingTime);

				while ((std::chrono::high_resolution_clock::now() - startTime) < targetTime) {}
			}
		}

		std::cout << std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000 << std::endl;

	}
}

void Game::HandleEvents()
{
	sf::Event evnt;

	while (window->pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			break;
		}
	}
}

void Game::Update(double dt)
{

}

void Game::Draw()
{
	window->clear();
	window->draw(hoopla);
	window->display();

}
