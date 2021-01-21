#pragma once
#include "Object.h"
#include "ObjectGuard.h"
#include "Entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>

enum class eBulletStates { neutral, active, shot };

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();
	void Initialize() override;
	void Destroy() override;
	void Update(const double in_dt) override;
	void Draw(std::shared_ptr<sf::RenderWindow> window) override;

	sf::Vector2f GetDirection() const { return m_direction; }
	eBulletStates GetState() const { return m_state; }
	std::shared_ptr<Entity> GetInstigator() const { return m_instigator; }

	void SetDirection(const sf::Vector2f& in_direction) { m_direction = in_direction; }
	void SetSpriteTexture(const sf::Texture& in_texture) { m_sprite.setTexture(in_texture); }
	void SetState(eBulletStates in_state) { m_state = in_state; }
	void SetInstigator(std::shared_ptr<Entity> in_entity) { m_instigator = in_entity; }

private:
	sf::Vector2f m_direction;
	bool m_isActive = false;
	eBulletStates m_state = eBulletStates::neutral;
	std::shared_ptr<Entity> m_instigator;
};