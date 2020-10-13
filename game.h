#pragma once
#include <iostream>
#include <chrono>
#include <thread>

class Game {
public:
	Game();
	void Run();
	void Update(double deltaTime);
	void Draw();
	void HandleEvents();

public:
	double deltaTime;
	double fps;

};
