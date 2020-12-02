#include "bullet.h"

Bullet::Bullet(sf::Vector2f in_position, sf::Vector2f in_dir)
{
	if (!texture.loadFromFile("Images/krabbyPatty.jpg")) {
		std::cout << "Failed to load burger" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	
	position = in_position;
	sprite.setPosition(position);

	speed = 15.0f;
	direction = in_dir;
	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;
}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	Entity::Initialize();
}

void Bullet::Destroy()
{
	Entity::Destroy();
}

void Bullet::Update()
{
	Entity::Update();
	Move(direction);
}

void Bullet::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	Entity::Draw(window);
}
