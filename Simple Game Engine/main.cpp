#include <iostream>
#include <SDL.h>
#include "Game.h"

using std::cout;
int main(int argc, char** argv)
{
	bool isGameInit = Game::instance().initialize();
	if (isGameInit) {
		Game::instance().load();
		Game::instance().loop();
		Log::info("Test");
		Game::instance().unload();
		Log::info("Test 2");
	}
	Game::instance().close();
	return 0;
}