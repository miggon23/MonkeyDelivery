#pragma once
#include <array>
#include "Texture.h"
#include <string>

#include <iostream>
#include <vector>

using namespace std;

const string IMAGES_PATH = "../Images/";

enum TextureName {
    monkeyTexture,
    monkeyEyesClosedTexture, // para la presentación del hito, se puede quitar después pq está en el spritesheet
   // spritesheet,
    energyTexture,
    energyLevelTexture,
    fearLevelTexture,
    woodPanel,
    missionPanelTexture,
    tucanTexture,
    mission1
};

const int NUM_TEXTURES = 9;

typedef struct {
    string filename;
    int numRows; int numCols;
} TextureAttributes;


const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] =
{ {"monkeyPrueba.png",1,1},
  {"animaciones mono/idle3.png",1,1},
 // {"animaciones mono/monkey.png",1,1}, // spritesheet
  {"energy.png",1,1},
  {"energyLevel.png",1,1},
  {"fearLevel.png",1,1},
  {"decorations/woodpanel.png",1,1},
  {"decorations/missionpanel.png",1,1},
  {"animals/tucan.png",1,1},
  {"decorations/Mision1.png",1,1}
};



class TextureContainer {

    array<Texture*, NUM_TEXTURES> textures;
    //vector<Texture*> textures;

public:
    TextureContainer(SDL_Renderer* renderer) { // SIN ARRAYS -> con vector
        //textures.resize(NUM_TEXTURES);

        std::cout << "Loading textures\n";
        for (int i = 0; i < NUM_TEXTURES; i++) {
            const TextureAttributes& attributes = TEXTURE_ATTRIBUTES[i];
            textures[i] = new Texture(renderer, IMAGES_PATH + attributes.filename, attributes.numRows, attributes.numCols);
        }
        std::cout << "Texture load finished\n";

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

