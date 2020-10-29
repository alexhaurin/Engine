#include "game.h"

Game::Game()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 800), "Engine2");

	Enemy enemy1(100.0, 100.0, 100.0);
	enemyList.push_back(enemy1);

	std::cout << "Game created" << std::endl;
}

Game::~Game()
{
	std::cout << "Game destroyed" << std::endl;
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
		//std::cout << std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000 << std::endl;
	}
}

void Game::HandleEvents()
{
	sf::Event event;

	inputState.Clear();
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			break;
		case sf::Event::KeyPressed:
			inputBool = true;

			//Inputs
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				std::cout << "pressed" << std::endl;
				inputState.keyUpPressed = true;
			}
			else
			{
				inputState.keyUpPressed = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				inputState.keyLeftPressed = true;
			}
			else
			{
				inputState.keyLeftPressed = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				inputState.keyDownPressed = true;
			}
			else
			{
				inputState.keyDownPressed = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				inputState.keyRightPressed = true;
			}
			else
			{
				inputState.keyRightPressed = false;
			}
		}
	}
}

void Game::Update(double dt)
{
	player.Update();
	player.CheckCollisions(enemyList);
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i].Update(player.GetPosition());
	}

	//Inputs
	if (inputState.keyUpPressed) {
		std::cout << "moved" << std::endl;
		player.sprite.move(0, -player.speed);
	}
	if (inputState.keyLeftPressed) {
		player.sprite.move(-player.speed, 0);
	}
	else if (inputState.keyDownPressed) {
		player.sprite.move(0, player.speed);
	}
	else if (inputState.keyRightPressed) {
		player.sprite.move(player.speed, 0);
	}
}

void Game::Draw()
{
	window->clear();

	window->draw(player.GetSprite());
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		window->draw(enemyList[i].GetSprite());
	}

	/*player.Draw();
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i].Draw();
	}*/

	window->display();
}

void Input::Clear()
{
	keyUpPressed = false;
	keyDownPressed = false;
	keyRightPressed = false;
	keyLeftPressed = false;
}
