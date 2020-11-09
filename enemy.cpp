#include "enemy.h"

Enemy::Enemy(float x, float y, float r)
{
	if (!texture.loadFromFile("Images/BrickCircle.png")) {
		std::cout << "Failed to load brick" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	sprite.setPosition(x, y);

	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;
	position = GetPosition();
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
	position = GetPosition();

	//Go to point given at certain speed
	sf::Vector2f vectorToPoint(point.x - position.x, point.y - position.y);
	sf::Vector2f movement = Normalize(vectorToPoint);
	sprite.move(movement.x * speed, movement.y * speed);
}

void Enemy::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

bool Enemy::CheckBulletCollisions(std::shared_ptr<Bullet> bullet)
{
	sf::Vector2f vector(position.x - bullet->GetPosition().x, position.y - bullet->GetPosition().y);
	float vectorMagnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

	if (vectorMagnitude >= bullet->GetDimensions().x / 2 + W / 2)
	{
		return false;
	}
	else
	{
		std::cout << "hit" << std::endl;
		return true;
	}
}

sf::Vector2f Enemy::Normalize(sf::Vector2f& vector)
{
	if (vector.x * vector.y == 0) {
		return vector;
	}

	float vectorMag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	sf::Vector2f normalizedVector(vector.x / vectorMag, vector.y / vectorMag);

	return normalizedVector;
}

sf::Sprite Enemy::GetSprite() const
{
	return sprite;
}

sf::Vector2f Enemy::GetPosition()
{
	sf::Vector2f p = sprite.getPosition();
	p.x += W / 2;
	p.y += H / 2;

	return p;
}

sf::Vector2f Enemy::GetDimensions() const
{
	return sf::Vector2f(W, H);
}
