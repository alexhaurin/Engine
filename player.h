#pragma once
#include "bullet.h"
#include "enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow> window);

	bool CheckCollisions(std::vector<std::shared_ptr<Enemy>> enemyList);
	void Shoot();

	sf::Vector2f GetPosition();

	std::vector<std::shared_ptr<Bullet>> bulletList;

public:
	sf::Sprite sprite;
	sf::Texture texture;

	float W;
	float H;

	sf::Vector2f position;
	sf::Vector2f direction;
	sf::Vector2f pastDirection;
	float speed;
};
