#include "game.h"

Game::Game()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 800), "Engine2");

	std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>(100.0, 100.0, 100.0);
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
	//	std::cout << std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count() / 1000 << std::endl;
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
sf::Vector2f normalize(sf::Vector2f& vector)
{
	if (vector.x * vector.y == 0) {
		return vector;
	}

	float vectorMag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	sf::Vector2f normalizedVector(vector.x / vectorMag, vector.y / vectorMag);

	return normalizedVector;
}

void Game::Update(double dt)
{
	player.Update();
	player.CheckCollisions(enemyList);
	for (unsigned int i = 0; i < player.bulletList.size(); i++) {
		player.bulletList[i]->Update();
	}
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Update(player.GetPosition());
	}

	if (inputState.keySpacePressed) {
		player.Shoot();
	}

	//Inputs
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

	player.sprite.move(normalize(player.direction) * player.speed);
}

void Game::Draw()
{
	window->clear();

	for (unsigned int i = 0; i < player.bulletList.size(); i++) {
		player.bulletList[i]->Draw(window);
	}
	player.Draw(window);
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		enemyList[i]->Draw(window);
	}

	window->display();
}

void Input::clearInputs()
{
	keyUpPressed = false;
	keyLeftPressed = false;
	keyDownPressed = false;
	keyRightPressed = false;
	keySpacePressed = false;
}

void Input::checkKeyboardInputs()
{
	clearInputs();
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
