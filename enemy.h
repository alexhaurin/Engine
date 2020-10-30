#pragma once
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy(float x, float y, float r);
	~Enemy();
	void Update(sf::Vector2f point);
	void Draw(std::shared_ptr<sf::RenderWindow> window);

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
