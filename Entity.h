#pragma once

#include "Object.h"
#include "ObjectGuard.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity : public Object
{
public:

	Entity();
	virtual ~Entity();
	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void Update();
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window);
	void Move(sf::Vector2f direction);

	sf::Sprite GetSprite() const { return sprite; }
	sf::Vector2f GetPosition() {
		sf::Vector2f pos = sprite.getPosition();
		return sf::Vector2f(pos.x + (W / 2), pos.y + (H / 2));
	}
	sf::Vector2f GetDimensions() const { return sf::Vector2f(W, H); }
	void SetPosition(sf::Vector2f in_pos) {
		sf::Vector2f centerPos(in_pos.x - (W / 2), in_pos.y - (H / 2));
		sprite.setPosition(centerPos);
	}

	//Math
	bool CheckCircleCollisions(sf::Vector2f objPos, float objRadius);
	bool CheckRectCollisions(sf::Vector2f objPos, sf::Vector2f objDimensions);
	sf::Vector2f Normalize(sf::Vector2f vector);

protected:
	sf::Vector2f position;
	float speed;

	float W;
	float H;

	sf::Texture texture;
	sf::Sprite sprite;
private:
};