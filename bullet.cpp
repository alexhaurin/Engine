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

	m_speed = 1.5f;

}

void Bullet::Destroy()
{
	Entity::Destroy();

	std::cout << "Bullet Destroyed" << std::endl;
}

void Bullet::Update(const double in_dt)
{
	Entity::Update(in_dt);
	Move(m_direction, m_speed * in_dt);
}

void Bullet::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	Entity::Draw(window);
}