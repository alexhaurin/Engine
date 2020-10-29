#pragma once
#include "enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();

	bool CheckCollisions(std::vector<Enemy>& enemyList);
	void Shoot();

	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	float GetSpeed();
	float GetWidth();
	float GetHeight();

	sf::Sprite sprite;
	sf::Texture texture;

	float W;
	float H;

	sf::Vector2f position;
	float speed = 10.0f;
};