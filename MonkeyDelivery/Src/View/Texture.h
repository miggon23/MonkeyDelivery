#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

using namespace std;
typedef unsigned int uint;

class Texture {
private:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;
    int w = 0;
    int h = 0;
    int fw = 0; // Frame width
    int fh = 0; // Frame height

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
    void render(const SDL_Rect& rect, double angle, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    // This rendering method corresponds to method SDL_RenderCopyEx.
    //
    // Renders part of the texture (src) to a destination rectangle (dest)
    // with a rotation (angle) around point p (of dest), and flips
    // according to the value of flip. If 'p'is nullptr, the rotation is done
    // wrt. the center

    inline void render(const SDL_Rect& src, const SDL_Rect& dest, double angle,
        const SDL_Point* p = nullptr,
        SDL_RendererFlip flip = SDL_FLIP_NONE) {
       
        SDL_RenderCopyEx(renderer, texture, &src, &dest, angle, p, flip);
    }
    // This rendering method corresponds to method SDL_RenderCopy.
    //
    // Renders part of the texture (src) to a destination rectangle (dest).
    // It can be implemented by calling the previous render method as well,
    // but we use SDL_RenderCopy directly since it does less checks so it
    // saves some checks ...
    inline void render(const SDL_Rect& src, const SDL_Rect& dest) {
        SDL_RenderCopy(renderer, texture, &src, &dest);
    }
    // render the complete texture at position (x,y).
    inline void render(int x, int y) {
        SDL_Rect dest = { x, y, w, h};
        render(dest);
    }

    // renders the complete texture at a destination rectangle (dest)
    inline void render(const SDL_Rect& dest) {
        SDL_Rect src = { 0, 0, w, h };
        render(src, dest);
    }

    inline void render() {

    }

    // renders the complete texture at a destination rectangle (dest),
    // with rotation
    /*inline void render(const SDL_Rect& dest, float rotation) {
        SDL_Rect src = { 0, 0, w, h };
        render(src, dest, rotation);
    }*/
    inline void changeAlpha(Uint8 alpha) {
        SDL_SetTextureBlendMode( texture,SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, alpha);
    }
};
