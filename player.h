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
	Player(sf::Texture in_texture, float in_scale, sf::Vector2f in_position);
	~Player() override;
	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;
	
	std::shared_ptr<Bullet> Shoot();

	sf::Vector2f GetDirection() const { return direction; }
	sf::Vector2f GetPastDirection() const { return pastDirection; }

	sf::Vector2f direction;

private:
	sf::Vector2f pastDirection;
};
