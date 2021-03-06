#include<iostream>
#include "Game.h"
#include"TextureManager.h"
#include"LoaderParams.h"
#include"InputHandler.h"
#include"Player.h"
#include"Enemy.h"

Game *Game::instance = 0;

bool Game::init(const char *title, int xPosition, int yPosition, int height, int width, bool fullScreen)
{
    int flags = SDL_WINDOW_SHOWN;

    if (fullScreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, xPosition, yPosition, height, width, flags);

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    TheInputHandler::getInstance()->initialiseJoysticks();
    TheTextureManager::getInstance()->load("assets/animate-alpha.png", "animate", renderer);

    Player *player = new Player(new LoaderParams(100, 100, 128, 82, "animate"));
    Enemy *enemy = new Enemy(new LoaderParams(300, 300, 128, 82, "animate"));

    gameObjects.push_back(player);
    gameObjects.push_back(enemy);

    running = true;
    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (std::vector<GameObject*>::size_type x = 0; x != gameObjects.size(); x++) {
        gameObjects[x]->draw();
    }

    //TheTextureManager::getInstance()->draw("animate", 0, 0, 128, 82, renderer);
    //TheTextureManager::getInstance()->drawFrame("animate", 100, 100, 128, 82, 1, currentFrame, renderer);

    SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
    TheInputHandler::getInstance()->update();
}

void Game::update()
{
    for (std::vector<GameObject*>::size_type x = 0; x != gameObjects.size(); x++) {
        gameObjects[x]->update();
    }

    currentFrame = int((SDL_GetTicks() / 100) % 6);
}

void Game::clean()
{
    TheInputHandler::getInstance()->clean();

    running = false;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
