#include "Game.h"

int main()
{
	Game game;

	srand(static_cast<unsigned>(time(0)));

	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
}