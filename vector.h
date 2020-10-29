#include <SFML/Graphics.hpp>

namespace vector {

	sf::Vector2f normalize(sf::Vector2f& vector)
	{
		if (vector.x * vector.y == 0) {
			std::cout << "0" << std::endl;
			return sf::Vector2f(1, 1);
		}

		float vectorMag = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
		sf::Vector2f normalizedVector(vector.x / vectorMag, vector.y / vectorMag);

		return normalizedVector;
	}
}