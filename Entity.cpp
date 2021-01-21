#include "Entity.h"
#include "VectorMath.h"

Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::Initialize() {

	Object::Initialize();

	//Sets sprite scale to match given dimensions when given texture size
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f((m_dimensions.x) / m_texture.getSize().x, (m_dimensions.x) / m_texture.getSize().x));
}

void Entity::Destroy() {

	Object::Destroy();
}

void Entity::Update(const double in_dt) {

	m_position = GetPosition();
}

void Entity::Draw(std::shared_ptr<sf::RenderWindow> window) {

	window->draw(m_sprite);
}

void Entity::Move(sf::Vector2f in_direction, float in_speed) {

	m_sprite.move(Math::Normalize(in_direction) * in_speed);
}

void Entity::GoToPoint(sf::Vector2f in_point, float in_speed) {

	sf::Vector2f vectorToPoint(in_point.x - m_position.x, in_point.y - m_position.y);
	sf::Vector2f movement = Math::Normalize(vectorToPoint);

	Move(movement, in_speed);
}

void Entity::OnBulletHit(std::shared_ptr<Bullet> in_bullet) {

}