#include "enemy.h"

Enemy::Enemy(sf::Texture in_texture, float in_radius, sf::Vector2f in_position)
{
	texture = in_texture;
	sprite.setTexture(texture);
	sprite.setPosition(in_position);

	//Sets sprite scale to match given radius when given texture size
	sprite.setScale(sf::Vector2f((in_radius * 2) / texture.getSize().x, (in_radius * 2) / texture.getSize().x));

	speed = 5.0f;
	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy()
{
	std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::Initialize()
{
	Entity::Initialize();
}

void Enemy::Destroy()
{
	Entity::Destroy();
}

void Enemy::Update()
{
	Entity::Update();
	//auto game = m_game;
	//const auto& player = game->GetPlayer();

	//Go to point given at certain speed
	/*sf::Vector2f point = player.GetPosition();
	sf::Vector2f vectorToPoint(point.x - position.x, point.y - position.y);
	sf::Vector2f movement = Normalize(vectorToPoint);

	Move(movement);*/
}

void Enemy::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	Entity::Draw(window);
}
