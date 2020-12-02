#pragma once
#include "enemy.h"
#include "player.h"
#include "Vector.h"
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

	std::shared_ptr<Player> GetPlayer() const { return player; }
	sf::Vector2i GetDimensions() const { return dimensions;  }

private:
	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<Entity> root;
	std::shared_ptr<Player> player;

	std::vector<std::shared_ptr<Entity>> entityList;
	std::vector<std::shared_ptr<Bullet>> bulletList;
	std::vector<std::shared_ptr<Enemy>> enemyList;
	std::vector<std::shared_ptr<Bullet>> bulletDestroyList;
	std::vector<std::shared_ptr<Enemy>> enemyDestroyList;

	std::vector<int> color{ 0, 255, 0 };
	sf::Vector2i dimensions;
	sf::Font robotoFont;

	Input inputState;
	bool inputBool;
};
