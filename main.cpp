#include <memory>
#include "game.h"

int main()
{
	auto game = std::make_shared<Game>();

	game->Run();
}
