#include "game.h"

Game::Game()
{
	dimensions = sf::Vector2i(1200, 800);
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(dimensions.x, dimensions.y), "Engine2");

	//Load
	if (!robotoFont.loadFromFile("Roboto-Bold.ttf")) {
		std::cout << "Failed to font" << std::endl;
	}

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Images/HooplaCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sf::Texture enemyTexture;
	if (!enemyTexture.loadFromFile("Images/BrickCircle.png")) {
		std::cout << "Failed to load brick" << std::endl;
	}

	//Spawn
	root = Object::SpawnRoot<Entity>();
	player = Object::Spawn<Player>(root, playerTexture, 100.0f, sf::Vector2f(100, 100));
	std::shared_ptr<Enemy> enemy1 = Object::Spawn<Enemy>(root, enemyTexture, 100.0f, sf::Vector2f(0, 0));
	std::shared_ptr<Enemy> enemy2 = Object::Spawn<Enemy>(root, enemyTexture, 100.0f, sf::Vector2f(500, 500));

	//Push
	enemyList.push_back(enemy1);
	enemyList.push_back(enemy2);

	entityList.push_back(player);
	for (auto enemy : enemyList)
	{
		entityList.push_back(enemy);
	}

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
	root->Update();
	player->Update();
	for (auto entity : entityList)
	{
		entity->Update();
	}

	color[0] = 0;
	color[1] = 255;

	//Check if out of screen
	if (!player->CheckRectCollisions(sf::Vector2f(dimensions.x / 2.0f, dimensions.y / 2.0f), sf::Vector2f(dimensions.x, dimensions.y)))
	{
		//Loop around
		if (player->GetPastDirection().x > 0)
		{
			player->SetPosition(sf::Vector2f(0 - (player->GetDimensions().x / 2), player->GetPosition().y));
		}
		else if (player->GetPastDirection().x < 0) {
			player->SetPosition(sf::Vector2f(dimensions.x + (player->GetDimensions().x / 2), player->GetPosition().y));
		}

		if (player->GetPastDirection().y < 0)
		{
			player->SetPosition(sf::Vector2f(player->GetPosition().x, dimensions.y + (player->GetDimensions().y / 2)));
		}
		else if (player->GetPastDirection().y > 0) {
			player->SetPosition(sf::Vector2f(player->GetPosition().x, 0 - (player->GetDimensions().y / 2)));
		}
	}

	//std::cout << enemyList[0]->GetPosition().x << ", " << enemyList[0]->GetPosition().y << std::endl;

	//Detect Collisions
	for (auto enemy : enemyList)
	{
		sf::Vector2f point = player->GetPosition();
		sf::Vector2f vectorToPoint(point.x - enemy->GetPosition().x, point.y - enemy->GetPosition().y);
		sf::Vector2f movement = enemy->Normalize(vectorToPoint);
		enemy->Move(movement);

		if (player->CheckCircleCollisions(enemy->GetPosition(), enemy->GetDimensions().x / 2))
		{
			color[0] = 255;
			color[1] = 0;
		}
	}

	for (std::shared_ptr<Enemy> enemy : enemyList)
	{
		for (std::shared_ptr<Bullet> bullet : bulletList)
		{
			if (enemy->CheckCircleCollisions(bullet->GetPosition(), bullet->GetDimensions().x))
			{
				color[2] = 200;

				enemyDestroyList.push_back(enemy);
				bulletDestroyList.push_back(bullet);
			}
			else {
				color[2] = 0;
			}
		}
	}

	//Inputs
	if (inputState.keySpacePressed)
	{
		auto bullet = (player->Shoot());
		bulletList.push_back(bullet);
		entityList.push_back(bullet);
	}

	if (inputState.keyUpPressed)
	{
		player->direction += sf::Vector2f(0, -1);
	}
	if (inputState.keyLeftPressed) {
		player->direction += sf::Vector2f(-1, 0);
	}
	if (inputState.keyDownPressed) {
		player->direction += sf::Vector2f(0, 1);
	}
	if (inputState.keyRightPressed) {
		player->direction += sf::Vector2f(1, 0);
	}

	player->Move(player->direction);
}

void Game::Draw()
{
	window->clear(sf::Color(color[0], color[1], color[2]));

	//Text
	sf::Text text("text", robotoFont, 50);
	text.setPosition(700, 700);

	window->draw(text);

	//Entities
	for (auto entity : entityList)
	{
		entity->Draw(window);
	}

	window->display();
}

////////////////////Input Class///////////////////
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
