#include <memory>
#include "game.h"
#include "enemy.h"

int main()
{
	auto game = std::make_shared<Game>();

	game->Run();
}
