#include "enemy.h"
#include "player.h"
#include "game.h"

Enemy::Enemy() {

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy() {

	std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::Initialize() {

	Entity::Initialize();

	//Sets sprite scale to match given radius when given texture size
	m_sprite.setScale(sf::Vector2f((m_dimensions.x * 2) / m_texture.getSize().x, (m_dimensions.x * 2) / m_texture.getSize().x));

	m_sprite.setTexture(m_texture);
	m_speed = 0.3f;
	m_dimensions.x = m_texture.getSize().x * m_sprite.getScale().x;
	m_dimensions.y = m_texture.getSize().y * m_sprite.getScale().y;
}

void Enemy::Destroy() {

	Entity::Destroy();
}

void Enemy::Update(double in_dt) {

	Entity::Update(in_dt);

	//auto game = m_game;
	auto player = m_game->GetPlayer();

	GoToPoint(sf::Vector2f(100, 100), m_speed * in_dt);
}

void Enemy::Draw(std::shared_ptr<sf::RenderWindow> window) {

	Entity::Draw(window);
}