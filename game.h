#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

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
	double fps;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Sprite hoopla;
};
