#include "bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	Entity::Initialize();

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	m_speed = 1.5f;
	m_dimensions.x = m_texture.getSize().x * m_sprite.getScale().x;
	m_dimensions.y = m_texture.getSize().y * m_sprite.getScale().y;
}

void Bullet::Destroy()
{
	Entity::Destroy();
}

void Bullet::Update(double in_dt)
{
	Entity::Update(in_dt);
	Move(m_direction, m_speed * in_dt);
}

void Bullet::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	Entity::Draw(window);
}