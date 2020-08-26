#include <string>

#include "engine/Timer.h"
#include "engine/Game.h"
#include "engine/Log.h"

LogConfig LOG_CONFIG = {};

// Use Graphics Card
#define DWORD unsigned int
#if defined(WIN32) || defined(_WIN32)
extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" { __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001; }
#else 
extern "C" { int NvOptimusEnablement = 1; }
extern "C" { int AmdPowerXpressRequestHighPerformance = 1; }
#endif

int main(int argc, char *argv[])
{
	const int SCREEN_WIDTH = 1080;
	const int SCREEN_HEIGHT = 600;

	// Init logging
	LOG_CONFIG.reporting_level = Debug;
	LOG_CONFIG.restart = true;
	if (LOG_CONFIG.restart) {
		Log::restart();
	}

	// Delta time in milliseconds
	unsigned int dt;
	Game game;
	game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	game.load();

	Timer timer;

	// Game loop
	while (game.isRunning) {
		dt = timer.computeDeltaTime();

		game.handleInputs();
		game.update(dt);
		game.render();

		// Delay frame if game runs too fast
		timer.delayTime();
	}

	// Exit game
	game.clean();
	return 0;
}
