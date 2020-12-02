#pragma once
#include "Object.h"
#include "ObjectGuard.h"
#include "Entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet : public Entity
{
public:
	Bullet(sf::Vector2f in_position, sf::Vector2f in_dir);
	~Bullet() override;
	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;

	sf::Vector2f GetDirection() const { return direction; }

private:
	sf::Vector2f direction;
};
