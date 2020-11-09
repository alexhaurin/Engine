#include "player.h"

Player::Player()
{
	if (!texture.loadFromFile("Images/HooplaCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));

	speed = 10.0f;
	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;
	position = GetPosition();

	std::cout << "Player created" << std::endl;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void Player::Update()
{
	position = GetPosition();
	if (direction != sf::Vector2f(0.0f, 0.0f)) {
		pastDirection = direction;
	}
	direction *= 0.0f;
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

void Player::Move(sf::Vector2f direction)
{
	sprite.move(Normalize(direction) * speed);
}

bool Player::CheckEnemyCollisions(std::vector<std::shared_ptr<Enemy>> enemyList)
{
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		sf::Vector2f vector(position.x - enemyList[i]->GetPosition().x, position.y - enemyList[i]->GetPosition().y);
		float vectorMagnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

		if (vectorMagnitude >= enemyList[i]->GetDimensions().x/2 + W/2)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

std::shared_ptr<Bullet> Player::Shoot() {
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(position.x, position.y, pastDirection);
	return bullet;
}

sf::Vector2f Player::Normalize(sf::Vector2f& vector)
{
	if (vector.x * vector.y == 0) {
		return vector;
	}

	float vectorMag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	sf::Vector2f normalizedVector(vector.x / vectorMag, vector.y / vectorMag);

	return normalizedVector;
}

sf::Vector2f Player::GetPosition()
{
	sf::Vector2f p = sprite.getPosition();
	p.x += W / 2;
	p.y += H / 2;

	return p;
}

float Player::GetSpeed() const
{
	return speed;
}
