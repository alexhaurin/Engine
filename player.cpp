#include "player.h"

Player::Player(sf::Texture in_texture, float in_radius, sf::Vector2f in_position)
{
	texture = in_texture;
	sprite.setTexture(texture);
	sprite.setPosition(in_position);

	//Sets sprite size to match given radius
	sprite.setScale(sf::Vector2f((in_radius * 2) / texture.getSize().x, (in_radius * 2) / texture.getSize().x));

	speed = 10.0f;
	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;

	std::cout << "Player created" << std::endl;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void Player::Initialize()
{
	Entity::Initialize();
}

void Player::Destroy()
{
	Entity::Destroy();
}

void Player::Update()
{
	Entity::Update();

	if (direction != sf::Vector2f(0.0f, 0.0f)) {
		pastDirection = direction;
	}
	direction *= 0.0f;
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	Entity::Draw(window);
}

std::shared_ptr<Bullet> Player::Shoot()
{
	auto bullet = Object::SpawnRoot<Bullet>(position, pastDirection);
	return bullet;
}
