#include "Game/Game.h"
#include "Win32/FrameworkMain.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

int main(int /*argc*/, char** /*argv*/)
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
