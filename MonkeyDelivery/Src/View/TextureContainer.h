#pragma once
#include <array>
#include "Texture.h"
#include <string>

using namespace std;

const string IMAGES_PATH = "../Images/";

enum TextureName {
    carTexture
};

const int NUM_TEXTURES = 1;

typedef struct {
    string filename;
    int numRows; int numCols;
} TextureAttributes;


const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] =
{ {"car.png",1,1}
};



class TextureContainer {

    array<Texture*, NUM_TEXTURES> textures;

public:
    TextureContainer(SDL_Renderer* renderer) {
        for (int i = 0; i < NUM_TEXTURES; i++) {
            const TextureAttributes& attributes = TEXTURE_ATTRIBUTES[i];
            textures[i] = new Texture(renderer, IMAGES_PATH + attributes.filename, attributes.numRows, attributes.numCols);
        }
    }

    ~TextureContainer() {
        for (int i = 0; i < NUM_TEXTURES; i++) {

            if (textures[i] != nullptr) {
                textures[i]->free();
            }
            delete textures[i];
        }
    }

    Texture* getTexture(TextureName name) const { return textures[name]; };

};

