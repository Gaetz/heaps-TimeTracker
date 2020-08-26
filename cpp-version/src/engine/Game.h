#ifndef GAME_H
#define GAME_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

#include <GL/glew.h>
#include <vector>
#include <memory>
#include "InputManager.h"
#include "Shader.h"
#include "RendererOGL.h"
#include "WindowSdl.h"

using std::unique_ptr;

class Scene;

// This game class manages game states and triggers their logic.
// It supports gamestate stacking. It does not implement a 
// gameobject/entity/whatever logic to let you free to choose
// your architecture.
class Game
{
public:
	Game();
	virtual ~Game();

	void init(int screenWidth, int screenHeight);
	void load();
	void handleInputs();
	void update(unsigned int dt);
	void render();
	void clean();

	void changeState(unique_ptr<Scene>);
	void pushState(unique_ptr<Scene>);
	void popState();

	bool isRunning;
	int windowWidth, windowHeight;

private:
	WindowSdl window;
	RendererOGL renderer;
	InputManager inputManager;
	std::vector<unique_ptr<Scene>> gameStates;
};

#endif