#include <memory>
#include "game.h"
#include "enemy.h"
#include "player.h"

int main()
{
	auto game = std::make_shared<Game>();

	game->Run();
}
