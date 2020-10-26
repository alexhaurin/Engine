#include "enemy.h"
	
Enemy::Enemy(double r)
{
	auto texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile("/Users/Alex Haurin/Downloads/HD_Hoopla_Fish.jpg")) {
		std::cout << "Failed to load hoopla" << std::endl;
	}
	sf::Sprite hoopla;
	hoopla.setTexture(*texture);

	radius = r;
	position = hoopla.getPosition();
}

void Enemy::Update()
{

}

bool Enemy::collisionCheck()
{
	sf::Vector2f object;
	double distance;
	distance = sqrt(pow(object.x - position.x, 2) + pow(object.y - position.y, 2));

	if (distance > radius)
	{
		return false;
	}
	else {
		return true;
	}
}