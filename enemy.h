#pragma once
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy(double radius);
	bool collisionCheck();
	void Update();
public:
	double radius;
	sf::Vector2f position;
};