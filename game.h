#pragma once
#include "enemy.h"
#include "player.h"
#include <chrono>
#include <thread>

class Input
{
public:
	void ClearInputs();
	void CheckKeyboardInputs();

	bool keyRightPressed = false;
	bool keyLeftPressed = false;
	bool keyUpPressed = false;
	bool keyDownPressed = false;
	bool keySpacePressed = false;
};

class Game
{
public:
	Game();
	~Game();

	void Run();
	void HandleEvents();
	void Update(double deltaTime);
	void Draw();

public:
	std::shared_ptr<sf::RenderWindow> window;

	Player player;
	std::vector<std::shared_ptr<Bullet>> bulletList;
	std::vector<std::shared_ptr<Enemy>> enemyList;
	std::vector<std::shared_ptr<Bullet>> bulletDestroyList;
	std::vector<std::shared_ptr<Enemy>> enemyDestroyList;
	Input inputState;
	bool inputBool;
};
