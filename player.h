#pragma once
#include "enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(float x, float y);
	~Bullet();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow> window);

	sf::Vector2f GetPosition();
	float GetSpeed();

private:
	sf::Sprite sprite;
	sf::Texture texture;

	float W;
	float H;

	sf::Vector2f position;
	float speed = 30.0f;
};

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow> window);

	bool CheckCollisions(std::vector<Enemy>& enemyList);
	void Shoot();

	sf::Vector2f GetPosition();
	sf::Sprite GetSprite();
	float GetSpeed();
	float GetWidth();
	float GetHeight();

	std::vector<Bullet> bulletList;

public:
	sf::Sprite sprite;
	sf::Texture texture;

	float W;
	float H;

	sf::Vector2f position;
	float speed = 10.0f;
};
