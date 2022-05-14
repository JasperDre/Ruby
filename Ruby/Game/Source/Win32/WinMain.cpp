#include "GamePCH.h"

#include "Game/Game.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int main()
{
	const auto framework = new Framework();
	framework->Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	const auto game = new Game(framework);
	framework->Run(game);
	framework->Shutdown();

	delete game;
	delete framework;

	return 0;
}
