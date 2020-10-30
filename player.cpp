#include "player.h"

Player::Player()
{
	//Set up sprite with proper scale and width/height
	if (!texture.loadFromFile("Images/HooplaCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));

	position = GetPosition();
	W = 543 / 5;
	H = 543 / 5;

	std::cout << "Player created" << std::endl;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void Player::Update()
{
	//Get position of sprite and offset it based on width
	position = sprite.getPosition();
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

bool Player::CheckCollisions(std::vector<Enemy>& enemyList)
{
	for (unsigned int i = 0; i < enemyList.size(); i++) {
		sf::Vector2f vector(position.x - enemyList[i].GetPosition().x, position.y - enemyList[i].GetPosition().y);
		float vectorMagnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

		if (vectorMagnitude >= enemyList[i].GetWidth()/2 + W/2)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void Player::Shoot() {
	Bullet bullet(position.x, position.y);
	bulletList.push_back(bullet);

	std::cout << "shoot" << std::endl;
}

sf::Vector2f Player::GetPosition()
{
	sf::Vector2f position = sprite.getPosition();
	position.x += W / 2;
	position.y += H / 2;

	return position;
}

sf::Sprite Player::GetSprite()
{
	return sprite;
}

float Player::GetSpeed()
{
	return speed;
}

float Player::GetWidth()
{
	return W;
}

float Player::GetHeight()
{
	return H;
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
//                Bullet                         //
///////////////////////////////////////////////////
///////////////////////////////////////////////////

Bullet::Bullet(float x, float y)
{
	//Set up sprite with proper scale and width/height
	if (!texture.loadFromFile("Images/HooplaCircle.png")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	sprite.setPosition(x, y);

	position = GetPosition();
	W = 543 / 5;
	H = 543 / 5;

	std::cout << "Bullet Created" << std::endl;
}

Bullet::~Bullet()
{
	std::cout << "Bullet Destroyed" << std::endl;
}

void Bullet::Update()
{
	position = sprite.getPosition();
	sprite.move(speed, 0);
}

void Bullet::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

sf::Vector2f Bullet::GetPosition()
{
	return sprite.getPosition();
}

float Bullet::GetSpeed()
{
	return speed;
}
