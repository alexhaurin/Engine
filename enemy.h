#pragma once
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy(float r, float x, float y);
	~Enemy();
	void Update(sf::Vector2f point);
	void Draw();

	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	float GetWidth();
	float GetHeight();

private:
	sf::Texture texture;
	sf::Sprite sprite;

	float W;
	float H;

	sf::Vector2f position;
	float speed;
};
