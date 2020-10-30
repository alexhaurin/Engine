#include "game.h"

Game::Game()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 800), "Engine2");

	Enemy enemy1(100.0, 100.0, 100.0);
	enemyList.push_back(enemy1);

	player.Shoot();

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
			inputState.checkKeyboardInputs();
		case sf::Event::KeyReleased:
			inputState.checkKeyboardInputs();
		}
	}
}

void Game::Update(double dt)
{
	player.Update();
	player.CheckCollisions(enemyList);
	for (unsigned int i = 0; i < player.bulletList.size(); i++) {
		player.bulletList[i].Update();
	}
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i].Update(player.GetPosition());
	}

	//Inputs
	if (inputState.keyUpPressed) {
		player.sprite.move(0, -player.speed);
	}
	else if (inputState.keyLeftPressed) {
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

	player.Draw(window);
	for (unsigned int i = 0; i < player.bulletList.size(); i++) {
		player.bulletList[i].Draw(window);
		std::cout << player.bulletList[i].GetPosition().x << ", " << player.bulletList[i].GetPosition().x << std::endl;
	}
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i].Draw(window);
	}

	window->display();
}

void Input::checkKeyboardInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		keyUpPressed = true;
	}
	else
	{
		keyUpPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		keyLeftPressed = true;
	}
	else
	{
		keyLeftPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		keyDownPressed = true;
	}
	else
	{
		keyDownPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		keyRightPressed = true;
	}
	else
	{
		keyRightPressed = false;
	}
}
