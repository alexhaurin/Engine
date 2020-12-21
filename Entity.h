#pragma once

#include "Object.h"
#include "ObjectGuard.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity : public Object {
public:
	Entity();
	virtual ~Entity();
	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void Update(double in_dt);
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window);

	void Move(sf::Vector2f in_direction, float in_speed);
	void GoToPoint(sf::Vector2f in_point, float in_speed);

	sf::Sprite GetSprite() const { return m_sprite; }
	sf::Vector2f GetDimensions() const { return m_dimensions; }
	float GetSpeed() const { return m_speed; }
	sf::Vector2f GetPosition() {
		sf::Vector2f pos = m_sprite.getPosition();
		return sf::Vector2f(pos.x + (m_dimensions.x / 2), pos.y + (m_dimensions.y / 2));
	}

	void SetTexture(const sf::Texture& in_texture) { m_texture = in_texture; }
	void SetDimensions(const sf::Vector2f& in_dimensions) { m_dimensions = in_dimensions; }
	void SetPosition(const sf::Vector2f& in_pos) {
		sf::Vector2f centerPos(in_pos.x - (m_dimensions.x / 2), in_pos.y - (m_dimensions.y / 2));
		m_sprite.setPosition(centerPos);
	}

protected:
	sf::Vector2f m_position;
	float m_speed;

	sf::Vector2f m_dimensions;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
private:
};