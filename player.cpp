#include "player.h"

Player::Player() {

	std::cout << "Player created" << std::endl;
}

Player::~Player() {
	std::cout << "Player destroyed" << std::endl;
}

void Player::Initialize() {

	Entity::Initialize();

	m_constSpeed = 1.0f;

	if (!m_bulletTexture.loadFromFile("Images/krabbyPatty.jpg")) {
		std::cout << "Failed to load burger" << std::endl;
	}
}

void Player::Destroy() {
	Entity::Destroy();
}

void Player::Update(const double in_dt) {
	Entity::Update(in_dt);

	m_speed = m_constSpeed - ((m_constSpeed/3) * m_ammoList.size());

	if (m_direction != sf::Vector2f(0.0f, 0.0f)) {
		m_pastDirection = m_direction;
	}
	m_direction *= 0.0f;

	for (auto bullet : m_ammoList) {
		bullet->SetPosition(m_position);
	}
}

void Player::Draw(std::shared_ptr<sf::RenderWindow> window) {
	Entity::Draw(window);
}

void Player::Shoot() {
	if (m_ammoList.empty()) { return; }

	auto bullet = m_ammoList[0];
	bullet->SetState(eBulletStates::shot);
	bullet->SetDirection(m_pastDirection);
	bullet->SetInstigator(shared_from_base<Player>());
	m_ammoList.erase(m_ammoList.begin());
}

void Player::AddToAmmoList(std::shared_ptr<Bullet> in_bullet) {
	if (m_ammoList.size() < m_maxAmmo) {
		in_bullet->SetState(eBulletStates::active);
		m_ammoList.push_back(in_bullet);
	}
}