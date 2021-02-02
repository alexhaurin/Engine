#include "enemy.h"
#include "game.h"
#include "VectorMath.h"

Enemy::Enemy() {

	std::cout << "Enemy created" << std::endl;
}

Enemy::~Enemy() {

	std::cout << "Enemy destroyed" << std::endl;
}

void Enemy::Initialize() {

	Entity::Initialize();

	m_speed = 0.3f;
	m_constSpeed = m_speed;

	StartWander();
}

void Enemy::Destroy() {

	Entity::Destroy();
}

void Enemy::Update(const double in_dt) {

	Entity::Update(in_dt);

	for (auto bullet : m_ammoList) {
		bullet->SetPosition(m_position);
	}

	auto game = m_game;

	switch (m_state) {
	case (eEnemyStates::wander):
		Wander(in_dt);
		break;
	case (eEnemyStates::stun):
		Stun(in_dt);
		break;
	case (eEnemyStates::attack):
		Attack(in_dt);
		break;
	case (eEnemyStates::pursue):
		Pursue(in_dt);
		break;
	default:
		std::cout << "Your statemachines broken bro" << std::endl;
	}
}

void Enemy::Draw(std::shared_ptr<sf::RenderWindow> window) {

	Entity::Draw(window);

	//Health bar
	auto pos = sf::Vector2f(m_position.x - (m_dimensions.x / 2), m_position.y + (m_dimensions.y / 2));
	auto border = sf::RectangleShape(sf::Vector2f(m_dimensions.x, m_dimensions.x / 5));
	border.setOutlineColor(sf::Color(0, 0, 0));
	border.setOutlineThickness(3);
	border.setFillColor(sf::Color(0, 0, 0, 0));
	border.setPosition(pos);

	auto bar = sf::RectangleShape(sf::Vector2f(m_dimensions.x * (m_health/100), m_dimensions.y/5));
	bar.setFillColor(sf::Color(255, 0, 0));
	bar.setPosition(pos);

	window->draw(bar);
	window->draw(border);
}

void Enemy::OnBulletHit(std::shared_ptr<Bullet> in_bullet) {
	SetStateTo(eEnemyStates::stun);
	m_health -= 10;

	if (IsValid(&*shared_from_base<Enemy>()) && m_health <= 0) {
		Destroy();
	}
	if (IsValid(&*in_bullet)) {
		in_bullet->Destroy();
	}
}

void Enemy::Shoot() {
	if (m_ammoList.empty()) { return; }

	auto bullet = m_ammoList[0];
	sf::Vector2f dir = Math::GetDirection(m_position, m_game->GetPlayer()->GetPosition());

	bullet->SetState(eBulletStates::shot);
	bullet->SetDirection(dir);
	bullet->SetInstigator(shared_from_base<Enemy>());
	bullet->SetSpeed(0.6f);


	m_ammoList.erase(m_ammoList.begin());
}

///////////////////////////////// State Machine //////////////////////////////////////////////

void Enemy::SetStateTo(eEnemyStates in_state) {

	switch (m_state) {
	case (eEnemyStates::wander):
		ExitWander();
		break;
	case (eEnemyStates::stun):
		ExitStun();
		break;
	case (eEnemyStates::attack):
		ExitAttack();
		break;
	case (eEnemyStates::pursue):
		ExitPursue();
		break;
	}

	switch (in_state) {
	case (eEnemyStates::wander):
		StartWander();
		break;
	case (eEnemyStates::stun):
		StartStun();
		break;
	case (eEnemyStates::attack):
		StartAttack();
		break;
	case (eEnemyStates::pursue):
		StartPursue();
		break;
	}
}

void Enemy::StartWander() {
	m_state = eEnemyStates::wander;
	m_speed = 0.1f;
	m_timerStart = std::chrono::steady_clock::now();
	m_wanderIdleTime = std::rand() % 1000 + 1000;
	m_wanderPoint.x = std::rand() % (int)(m_game->GetDimensions().x - (m_dimensions.x / 2));
	m_wanderPoint.y = std::rand() % (int)(m_game->GetDimensions().y - (m_dimensions.y / 2));

	Wander(m_game->GetFramerate());
}

void Enemy::Wander(const double in_dt) {

	auto timePassed = std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - m_timerStart).count();

	if (timePassed < 3000) {}
	else {
		GoToPoint(m_wanderPoint, m_speed * in_dt);
	}

	if (m_position.x - 10 < m_wanderPoint.x && m_position.x + 10 > m_wanderPoint.x) {
		StartWander();
	}
}

void Enemy::ExitWander() {
	m_speed = m_constSpeed;
}

void Enemy::StartStun() {
	m_state = eEnemyStates::stun;

	m_timerStart = std::chrono::steady_clock::now();
	m_stunTime = std::rand() % 1000 + 3000;

	m_rotAngle = 50;
	m_rotRadius = 10.0;
	m_rotCenter = m_position;

	Stun(m_game->GetFramerate());
}

void Enemy::Stun(const double in_dt) {

	auto timePassed = std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - m_timerStart).count();
	
	//Problem with getting posY, increases too much
	auto posX = m_rotCenter.x + cos(m_rotAngle * (3.14 / 180.0)) * m_rotRadius;
	auto posY = m_rotCenter.x + sin(m_rotAngle * (3.14 / 180.0)) * m_rotRadius;
	m_rotAngle += 0.2 * in_dt;

	SetPosition(sf::Vector2f(posX, posY));

	if (timePassed >= m_stunTime) {
		ExitStun();
	}

}

void Enemy::ExitStun() {
	StartAttack();
}

void Enemy::StartAttack() {
	m_state = eEnemyStates::attack;
	m_speed = 0.2f;

	Attack(m_game->GetFramerate());
}

void Enemy::Attack(const double in_dt) {

	auto distance = sf::Vector2f(m_game->GetPlayer()->GetPosition().x - m_position.x, m_game->GetPlayer()->GetPosition().y - m_position.y);
	if (Math::GetMagnitude(distance) <= m_pursueDistance) {
		SetStateTo(eEnemyStates::pursue);
		return;
	}

	std::shared_ptr<Bullet> tBullet;

	if (m_ammoList.empty()) {
		for (auto bullet : m_game->GetBulletList()) {
			if (bullet->GetState() == eBulletStates::neutral) {
				tBullet = bullet;
				break;
			}
		}

		if (tBullet == nullptr) {
			SetStateTo(eEnemyStates::pursue);
			return;
		}

		GoToPoint(tBullet->GetPosition(), m_speed * in_dt);

		if (Math::CheckCircleCollisions(m_position, m_dimensions.x / 2, tBullet->GetPosition(), tBullet->GetDimensions().x / 2)) {
			m_ammoList.push_back(tBullet);
			m_timerStart = std::chrono::steady_clock::now();
		}
	}
	else {
		auto timePassed = std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - m_timerStart).count();
		if (timePassed > 1000) {
			Shoot();
		}

	}
}

void Enemy::ExitAttack() {
	Shoot();

	m_speed = m_constSpeed;
}

void Enemy::StartPursue() {
	m_state = eEnemyStates::pursue;
	m_speed = std::min(1.0f, m_constSpeed + (3 / m_health));

	Pursue(m_game->GetFramerate());
}

void Enemy::Pursue(const double in_dt) {

	auto distance = sf::Vector2f(m_game->GetPlayer()->GetPosition().x - m_position.x, m_game->GetPlayer()->GetPosition().y - m_position.y);
	if (Math::GetMagnitude(distance) > m_pursueDistance && !m_game->GetNeutralBulletList().empty()) {
		SetStateTo(eEnemyStates::attack);
		return;
	}

	auto player = m_game->GetPlayer();

	GoToPoint(player->GetPosition(), m_speed * in_dt);

}

void Enemy::ExitPursue() {
	m_speed = m_constSpeed;
}