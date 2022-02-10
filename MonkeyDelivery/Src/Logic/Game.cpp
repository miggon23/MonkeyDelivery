#include "Game.h"

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{
 
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;
}

string Game::getGameName() {
    return name;
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}