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
	void Update(double in_dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;
	
	std::shared_ptr<Bullet> Shoot();
	std::shared_ptr<Bullet> CreateBullet(sf::Texture& in_texture, const sf::Vector2f& in_position, sf::Vector2f in_direction);

	sf::Vector2f GetDirection() const { return m_direction; }
	sf::Vector2f GetPastDirection() const { return m_pastDirection; }

	void SetIsTouchingEnemy(bool in_isTouching) { isTouchingEnemy = in_isTouching; }
	bool GetIsTouchingEnemy() { return isTouchingEnemy; }

	sf::Vector2f m_direction;

private:
	bool isTouchingEnemy;
	sf::Vector2f m_pastDirection;
	sf::Texture m_bulletTexture;
};