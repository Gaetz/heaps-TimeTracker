#include "../engine/Game.h"
#include "../engine/Assets.h"
#include "../engine/Scene.h"

#include "SceneMain.h"

Game::Game() : isRunning(false),
               windowWidth(0),
               windowHeight(0),
               window("Time Tracker") 
{
}

Game::~Game() 
{
    SDL_Quit();
}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    bool isWindowInit = window.initialize(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, false, "Time Tracker");
    window.logGlParams();
	bool isRendererInit = renderer.initialize(window);
    isRunning = true;
}

void Game::load() {
    // Game state
    changeState(std::make_unique<SceneMain>());
}

void Game::handleInputs() {
    inputManager.prepareForUpdate();
    isRunning = inputManager.pollInputs();
    const InputState &inputState = inputManager.getState();
    gameStates.back()->handleEvent(inputState);
}

void Game::update(unsigned int dt) {
    window.updateFpsCounter(dt);
    gameStates.back()->update(dt);
}

void Game::render() {
    renderer.beginDraw();
    gameStates.back()->draw();
    renderer.endDraw();
    window.swapBuffer();
}

void Game::clean() {
    Assets::clear();
    window.clean();
}

void Game::changeState(unique_ptr<Scene> state) {
    // cleanup the current state
    if (!gameStates.empty()) {
        gameStates.back()->clean();
        gameStates.pop_back();
    }

    // store and load the new state
    state->setGame(this);
    gameStates.push_back(std::move(state));
    gameStates.back()->load();
}

void Game::pushState(unique_ptr<Scene> state) {
    // pause current state
    if (!gameStates.empty()) {
        gameStates.back()->pause();
    }

    // store and init the new state
    gameStates.push_back(std::move(state));
    gameStates.back()->load();
}

void Game::popState() {
    // cleanup the current state
    if (!gameStates.empty()) {
        gameStates.back()->clean();
        gameStates.pop_back();
    }

    // resume previous state
    if (!gameStates.empty()) {
        gameStates.back()->resume();
    }
}