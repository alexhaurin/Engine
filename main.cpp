#include <memory>
#include "game.h"

int main() {

	Game game;

	std::shared_ptr<Game> gamePointer = std::make_shared<Game>();

	game.Run();


}