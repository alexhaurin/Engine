#include "Entity.h"

Entity::Entity()
{
	position = GetPosition();
	speed = 10.0f;
	W = texture.getSize().x * sprite.getScale().x;
	H = texture.getSize().y * sprite.getScale().y;
}

Entity::~Entity()
{

}

void Entity::Initialize()
{
	Object::Initialize();

//	std::cout << "Initializing entity" << std::endl;
}

void Entity::Destroy()
{
	std::cout << "Destroying entity" << std::endl;

	Object::Destroy();
}

void Entity::Update()
{
	position = GetPosition();
}

void Entity::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
}

void Entity::Move(sf::Vector2f direction)
{
	sprite.move(Normalize(direction) * speed);
}

////////////////////////Math////////////////////////////

bool Entity::CheckCircleCollisions(sf::Vector2f objPos, float objRadius)
{
	sf::Vector2f vector(position.x - objPos.x, position.y - objPos.y);
	float vectorMagnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

	return (vectorMagnitude <= objRadius + W / 2);
}

bool Entity::CheckRectCollisions(sf::Vector2f objPos, sf::Vector2f objDimensions) {
	//Set position to top left corner
	objPos.x -= objDimensions.x / 2;
	objPos.y -= objDimensions.y / 2;


	if ((position.x + W / 2 >= objPos.x && position.x - W / 2 <= objPos.x + objDimensions.x) && \
		(position.y + H / 2 >= objPos.y && position.y - H / 2 <= objPos.y + objDimensions.y))
	{
		return true;
	}

	return false;
}

sf::Vector2f Entity::Normalize(sf::Vector2f vector)
{
	if (vector.x * vector.y == 0) {
		return vector;
	}

	float vectorMag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	sf::Vector2f normalizedVector(vector.x / vectorMag, vector.y / vectorMag);

	return normalizedVector;
}