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

	void Move(sf::Vector2f direction);
	bool CheckEnemyCollisions(std::vector<std::shared_ptr<Enemy>> enemyList);
	std::shared_ptr<Bullet> Shoot();
	sf::Vector2f Normalize(sf::Vector2f& vector);

	sf::Vector2f GetPosition();
	float GetSpeed() const;

	sf::Vector2f direction;

private:
	sf::Texture texture;
	sf::Sprite sprite;

	float W;
	float H;
	sf::Vector2f position;
	sf::Vector2f pastDirection;

	float speed;
};
