#include "player.h"

Player::Player() {

	std::cout << "Player created" << std::endl;
}

Player::~Player() {
	std::cout << "Player destroyed" << std::endl;
}

void Player::Initialize() {

	//Sets sprite size to match given radius
	m_sprite.setScale(sf::Vector2f((m_dimensions.x * 2) / m_texture.getSize().x, (m_dimensions.x * 2) / m_texture.getSize().x));

	m_sprite.setTexture(m_texture);
	m_speed = 1.0f;
	m_dimensions.x = m_texture.getSize().x * m_sprite.getScale().x;
	m_dimensions.y = m_texture.getSize().y * m_sprite.getScale().y;

	if (!m_bulletTexture.loadFromFile("Images/krabbyPatty.jpg")) {
		std::cout << "Failed to load burger" << std::endl;
	}

	Entity::Initialize();
}

void Player::Destroy() {
	Entity::Destroy();
}

void Player::Update(double in_dt) {
	Entity::Update(in_dt);

	if (m_direction != sf::Vector2f(0.0f, 0.0f)) {
		m_pastDirection = m_direction;
	}
	m_direction *= 0.0f;
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window) {
	Entity::Draw(window);
}

std::shared_ptr<Bullet> Player::Shoot() {
	auto bullet = CreateBullet(m_bulletTexture, m_position, m_pastDirection);
	return bullet;
}

std::shared_ptr<Bullet> Player::CreateBullet(sf::Texture& in_texture, const sf::Vector2f& in_position, sf::Vector2f in_direction) {
	auto bullet = SpawnWithSetup<Bullet>(shared_from_this(), [this, in_texture, in_position, in_direction](Bullet* in_bullet) {
		in_bullet->SetTexture(in_texture);
		in_bullet->SetPosition(in_position);
		in_bullet->SetDimensions(sf::Vector2f(100.0, 100.0));;
		in_bullet->SetDirection(in_direction);
	});
	return bullet;
}