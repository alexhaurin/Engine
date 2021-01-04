#pragma once

#include "bullet.h"
#include "Entity.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy : public Entity {
public:
	Enemy();
	~Enemy();
	void Initialize() override;
	void Destroy() override;

	void Update(double in_dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;
};