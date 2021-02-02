#pragma once

#include "bullet.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

class Player;

enum class eEnemyStates { wander, stun, pursue, attack};

class Enemy : public Entity {
public:
	Enemy();
	~Enemy();
	void Initialize() override;
	void Destroy() override;

	void Update(const double in_dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;
	void OnBulletHit(std::shared_ptr<Bullet> in_bullet) override;
	void Shoot();

	void SetStateTo(eEnemyStates in_state);
	void StartWander();
	void Wander(const double in_dt);
	void ExitWander();
	void StartStun();
	void Stun(const double in_dt);
	void ExitStun();
	void StartAttack();
	void Attack(const double in_dt);
	void ExitAttack();
	void StartPursue();
	void Pursue(const double in_dt);
	void ExitPursue();

	float GetHealth() const { return m_health; }
	eEnemyStates GetState() const { return m_state; }

	void SetHealth(float in_health) { m_health = in_health; }

private:
	float m_health = 100;

	eEnemyStates m_state;
	std::vector<std::shared_ptr<Bullet>> m_ammoList;

	float m_pursueDistance = 300;

	std::chrono::time_point<std::chrono::steady_clock> m_timerStart;
	sf::Vector2f m_wanderPoint;
	float m_wanderIdleTime;

	sf::Vector2f m_rotCenter;
	float m_rotAngle;
	float m_rotRadius;

	float m_stunTime;
};