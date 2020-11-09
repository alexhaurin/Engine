#pragma once
#include "bullet.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy(float x, float y, float r);
	~Enemy();
	void Update(sf::Vector2f point);
	void Draw(std::shared_ptr<sf::RenderWindow> window);
	bool CheckBulletCollisions(std::shared_ptr<Bullet> bullet);
	sf::Vector2f Normalize(sf::Vector2f& vector);
	
	sf::Vector2f GetPosition();
	sf::Sprite GetSprite() const;
	sf::Vector2f GetDimensions() const;

private:
	sf::Texture texture;
	sf::Sprite sprite;

	float W;
	float H;

	sf::Vector2f position;
	float speed;
};
