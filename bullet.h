#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(float x, float y, sf::Vector2f d);
	~Bullet();
	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow> window);

	sf::Vector2f GetPosition();
	sf::Vector2f GetDimensions() const;

private:
	sf::Sprite sprite;
	sf::Texture texture;

	float W;
	float H;

	sf::Vector2f position;
	float speed;
	sf::Vector2f direction;
};
