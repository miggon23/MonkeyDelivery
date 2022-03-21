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
    monkeyEyesClosedTexture, // para la presentaci�n del hito, se puede quitar despu�s pq est� en el spritesheet
   // spritesheet,
    energyTexture,
    energyLevelTexture,
    fearLevelTexture,
    missionPanelTexture,
    woodPanelTexture,
    tucanTexture,
    catTexture,
    batTexture,
    mission1Texture,
    mission2Texture,
    cama,
    dialogoPrueba,
    bullTexture,
    monkeyspritesheet,
    batspritesheet,
    bullspritesheet,
    catspritesheet,
    startButtonTexture,
    scorpionSpritesheet,
    shopTexture,
    shopPanel,
    seleccionShopPanel,
    plantSpritesheet,
    optionsButtonTexture,
    backButtonTexture,
    sliderBase,
    sliderClicker,
    pauseButtonTexture,
    menuButtonTexture
};


const int NUM_TEXTURES = 31;



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
  {"catPrueba.png",1,1},
  {"batPrueba.png",1,1},
  {"decorations/Mision1.png",1,1},
  {"decorations/Mision1.png",1,1},
  {"decorations/cama.jpg",1,1},
  {"dialogPrueba.png",1,1},
  {"bull.png",1,1},
  {"animaciones mono/monkey.png",1,1},
  {"enemies/bat.png",1,1},
  {"enemies/bull.png",1,1},
  {"enemies/cat.png",1,1},
  {"Buttons/startButton.png",1,1},
  {"enemies/scorpion.png",1,1},
  {"shop.png",1,1},
  {"shop/panelShop.png",1,1},
  {"shop/seleccion.png",1,1},
  {"enemies/plant.png",1,1},
  {"Buttons/options.png",1,1},
  {"Buttons/back.png",1,1},
  {"ui/sliderBase.png",1,1},
  {"ui/sliderClicker.png",1,1},
  {"Buttons/pause.png",1,1},
  {"Buttons/backMenu.png",1,1}

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

