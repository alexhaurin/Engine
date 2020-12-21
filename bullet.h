#pragma once
#include "Object.h"
#include "ObjectGuard.h"
#include "Entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();
	void Initialize() override;
	void Destroy() override;
	void Update(double in_dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;

	sf::Vector2f GetDirection() const { return m_direction; }

	void SetDirection(const sf::Vector2f& in_direction) { m_direction = in_direction; }
	void SetSpriteTexture(const sf::Texture& in_texture) { m_sprite.setTexture(in_texture); }

private:
	sf::Vector2f m_direction;
};