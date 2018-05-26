#include "GameEngine.h"
#include "PlayState.h"

int main(int argc, char *argv[])
{
	iae::GameEngine game;
	iae::PlayState playstate;
	// initialize the engine
	// Santa resolution: 1024*576
	// Game tiles: 32 x 16
	// HUD: 64px
	game.Init("SantaWin32", 1024, 576, false);

	// load the intro
	game.ChangeState(&playstate);

	// main loop
	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	// cleanup the engine
	game.Cleanup();
	return 0;
}