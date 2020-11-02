#include "bullet.h"

Bullet::Bullet(float x, float y, sf::Vector2f d)
{
	if (!texture.loadFromFile("Images/krabbyPatty.jpg")) {
		std::cout << "Failed to load burger" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	sprite.setPosition(x, y);

	speed = 30.0f;
	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;
	position = GetPosition();
	direction = d;

	//std::cout << "Bullet Created" << std::endl;
}

Bullet::~Bullet()
{
	//std::cout << "Bullet Destroyed" << std::endl;
}

void Bullet::Update()
{
	position = GetPosition();
	sprite.move(direction * 30.0f);
}

void Bullet::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

sf::Vector2f Bullet::GetPosition()
{
	sf::Vector2f p = sprite.getPosition();
	p.x += W / 2;
	p.y += H / 2;

	return p;
}