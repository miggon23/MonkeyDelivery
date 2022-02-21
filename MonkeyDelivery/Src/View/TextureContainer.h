#pragma once
#include <array>
#include "Texture.h"
#include <string>

#include <iostream>

using namespace std;

const string IMAGES_PATH = "../Images/";

enum TextureName {
    monkeyTexture,
    energyTexture,
    energyLevelTexture,
    back1,back2,
    front1,front2,front3,
    idle1,idle2,idle3,idle4,idle5,
    side1,side2,side3,side4,side5,
    woodPanel,
    missionPanel,
    tucanTexture
};

const int NUM_TEXTURES = 21;

typedef struct {
    string filename;
    int numRows; int numCols;
} TextureAttributes;


const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] =
{ {"monkeyPrueba.png",1,1},
  {"energy.png",1,1},
  {"energyLevel.png",1,1},
  {"animaciones mono/back1.png",1,1},
  {"animaciones mono/back2.png",1,1},
  {"animaciones mono/front1.png",1,1},
  {"animaciones mono/front2.png",1,1},
  {"animaciones mono/front3.png",1,1},
  {"animaciones mono/idle1.png",1,1},
  {"animaciones mono/idle2.png",1,1},
  {"animaciones mono/idle3.png",1,1},
  {"animaciones mono/idle4.png",1,1},
  {"animaciones mono/idle5.png",1,1},
  {"animaciones mono/side1.png",1,1},
  {"animaciones mono/side2.png",1,1},
  {"animaciones mono/side3.png",1,1},
  {"animaciones mono/side4.png",1,1},
  {"animaciones mono/side5.png",1,1},
  {"decorations/woodpanel.png",1,1},
  {"decorations/missionpanel.png",1,1},
  {"animals/tucan.png",1,1}
};



class TextureContainer {

    array<Texture*, NUM_TEXTURES> textures;

public:
    TextureContainer(SDL_Renderer* renderer) { // SIN ARRAYS -> con vector
        std::cout << "Entrandoo\n";
        for (int i = 0; i < NUM_TEXTURES; i++) {
            const TextureAttributes& attributes = TEXTURE_ATTRIBUTES[i];
            textures[i] = new Texture(renderer, IMAGES_PATH + attributes.filename, attributes.numRows, attributes.numCols);
        }
        std::cout << "out\n";

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

