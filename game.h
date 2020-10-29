#pragma once
#include "enemy.h"
#include "player.h"
#include <chrono>
#include <thread>

class Input
{
public:
	void Clear();

	bool keyRightPressed;
	bool keyLeftPressed;
	bool keyUpPressed;
	bool keyDownPressed;
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
	std::vector<Enemy> enemyList;
	Input inputState;
	bool inputBool;
};
