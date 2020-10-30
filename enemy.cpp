#include "enemy.h"
#include "vector.h"

Enemy::Enemy(float x, float y, float r)
{
	if (!texture.loadFromFile("Images/BrickCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.333f, 0.333f));
	sprite.setPosition(x, y);

	position = GetPosition();
	W = 225 / 3;
	H = 225 / 3;

	position.x = x;
	position.y = y;
	speed = 2.0f;

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
	std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::Update(sf::Vector2f point)
{
	//Get position of sprite and offset it based on width
	position = sprite.getPosition();
	position.x += W / 2;
	position.y += W / 2;

	//Go to point given at certain speed
	sf::Vector2f vectorToPoint(point.x - position.x, point.y - position.y);
	sf::Vector2f movement = vector::normalize(vectorToPoint);
	sprite.move(movement.x * speed, movement.y * speed);
}

void Enemy::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

sf::Sprite Enemy::GetSprite()
{
	return sprite;
}

sf::Vector2f Enemy::GetPosition()
{
	sf::Vector2f position = sprite.getPosition();
	position.x += W / 2;
	position.y += H / 2;

	return position;
}

float Enemy::GetWidth()
{
	return W;
}

float Enemy::GetHeight()
{
	return H;
}
