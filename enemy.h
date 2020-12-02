#pragma once

#include "bullet.h"
#include "Entity.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Enemy : public Entity
{
public:
	Enemy(sf::Texture in_texture, float in_scale, sf::Vector2f in_position);
	~Enemy() override;
	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;

private:
	//std::shared_ptr<Game> m_game;
};
