#include "game.h"

Game::Game()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 800), "Engine2");

	std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>(100.0, 100.0, 100.0);
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
			inputState.CheckKeyboardInputs();
		case sf::Event::KeyReleased:
			inputState.CheckKeyboardInputs();
		}
	}
}

void Game::Update(double dt)
{
	//Update
	player.Update();
	for (unsigned int i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Update();
	}
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Update(player.GetPosition());
	}

	//Detect Collisions
	player.CheckEnemyCollisions(enemyList);
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		for (unsigned int j = 0; j < bulletList.size(); j++) {
			if (enemyList[i]->CheckBulletCollisions(bulletList[j]))
			{
				enemyDestroyList.push_back(enemyList[i]);
				bulletDestroyList.push_back(bulletList[j]);
			}
		}
	}


	//Inputs
	if (inputState.keySpacePressed) {
		bulletList.push_back(player.Shoot());
	}

	if (inputState.keyUpPressed) {
		player.direction += sf::Vector2f(0, -1);
	}
	if (inputState.keyLeftPressed) {
		player.direction += sf::Vector2f(-1, 0);
	}
	if (inputState.keyDownPressed) {
		player.direction += sf::Vector2f(0, 1);
	}
	if (inputState.keyRightPressed) {
		player.direction += sf::Vector2f(1, 0);
	}

	player.Move(player.direction);
}

void Game::Draw()
{
	window->clear();

	player.Draw(window);
	for (unsigned int i = 0; i < bulletList.size(); i++) {
		bulletList[i]->Draw(window);
	}
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Draw(window);
	}

	window->display();
}

void Input::ClearInputs()
{
	keyUpPressed = false;
	keyLeftPressed = false;
	keyDownPressed = false;
	keyRightPressed = false;
	keySpacePressed = false;
}

void Input::CheckKeyboardInputs()
{
	ClearInputs();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		keyUpPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		keyLeftPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		keyDownPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		keyRightPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		keySpacePressed = true;
	}
}
