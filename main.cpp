#include <memory>
#include "game.h"

int main() {
	auto game = std::make_shared<Game>();


	/*sf::RenderWindow window(sf::VideoMode(1200, 800), "Engine2", sf::Style::Default);
	sf::Event evnt;

	while (window.isOpen()) {
		while (window.pollEvent(evnt)) {

			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			}
		}
	} */


	game->Run();
}
