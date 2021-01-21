#pragma once
#include "bullet.h"
#include "enemy.h"
#include "Object.h"
#include "ObjectGuard.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Player : public Entity
{
public:
	Player();
	~Player();
	void Initialize() override;
	void Destroy() override;
	void Update(const double in_dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;
	
	void Shoot();

	bool GetIsTouchingEnemy() { return isTouchingEnemy; }
	sf::Vector2f GetDirection() const { return m_direction; }
	sf::Vector2f GetPastDirection() const { return m_pastDirection; }
	std::vector<std::shared_ptr<Bullet>> GetAmmoList() const { return m_ammoList; }

	void SetIsTouchingEnemy(bool in_isTouching) { isTouchingEnemy = in_isTouching; }
	void AddToAmmoList(std::shared_ptr<Bullet> in_bullet);

	sf::Vector2f m_direction;

private:
	bool isTouchingEnemy;
	sf::Vector2f m_pastDirection;
	sf::Texture m_bulletTexture;
	
	std::vector<std::shared_ptr<Bullet>> m_ammoList;
	int m_maxAmmo = 1;
};