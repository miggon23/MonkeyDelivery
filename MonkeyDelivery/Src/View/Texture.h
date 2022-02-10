#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;
typedef unsigned int uint;

class Texture {
private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    uint w = 0;
    uint h = 0;
    uint fw = 0; // Frame width
    uint fh = 0; // Frame height

public:
    Texture(SDL_Renderer* r) : renderer(r) {};
    Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
    Texture(Texture& t) = delete;
    ~Texture() { free(); };
    void free();

    int getW() const { return w; };
    int getH() const { return h; };
    SDL_Texture* getTexture() const { return texture; };

    void load(string filename, uint numRows = 1, uint numCols = 1);
    void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};
