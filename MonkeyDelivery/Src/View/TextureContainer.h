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
	plantSpritesheet,
	scorpionSpritesheet,
	
	startButtonTexture,
	shopTexture,
	shopPanel,
	seleccionShopPanel,
	optionsButtonTexture,
	backButtonTexture,
	sliderBase,
	sliderClicker,
	pauseButtonTexture,
	menuButtonTexture,
	creditsButtonTexture,
	continueButtonTexture,
	flashlightUp,
	flashlightDown,
	flashlightSides,
	linternaProvi,
	bikeTexture,
	skatesTexture,
	drinkTexture,
	flashlightTexture,

	batDyingSpritesheet,
	bullDyingSpritesheet,
	catDyingSpritesheet,
	plantDyingSpritesheet,
	scorpionDyingSpritesheet,
	BrightnessTexture,
	FadeOutTexture,
	capibaraTexture
};


const int NUM_TEXTURES = 49;



typedef struct {
	string filename;
	int numRows; int numCols;
} TextureAttributes;


const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] =
{ {"monkeyPrueba.png",1,1},
  {"animaciones mono/idle3.png",1,1},
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
  {"decorations/bed.png",1,1},
  {"ui/dialoguebox.png",1,1},
  {"bull.png",1,1},
  {"animaciones mono/monkey_.png",1,1},
  {"enemies/bat.png",1,1},
  {"enemies/bull.png",1,1},
  {"enemies/cat.png",1,1},
  {"enemies/plant.png",1,1},
  {"enemies/scorpion.png",1,1},
  {"Buttons/startButton.png",1,1},
  {"shop/transparent.png",1,1},
  {"shop/panelShop.png",1,1},
  {"shop/seleccion.png",1,1},
  {"Buttons/options.png",1,1},
  {"Buttons/back.png",1,1},
  {"ui/sliderBase.png",1,1},
  {"ui/sliderClicker.png",1,1},
  {"Buttons/pause.png",1,1},
  {"Buttons/backMenu.png",1,1},
  {"Buttons/credits.png",1,1},
  {"Buttons/continue.png",1,1},
  {"objects/linterna_up.png",1,1},
  {"objects/linterna_down.png",1,1},
  {"objects/linterna_left.png",1,1},
  {"objects/luzprovi.png",1,1},
  {"objects/patinete.png",1,1},
  {"objects/patines.png",1,1},
  {"objects/refresco.png",1,1},
  {"objects/linterna2.png",1,1},

  {"enemies/bat_dying.png",1,1},
  {"enemies/bull_dying.png",1,1},
  {"enemies/cat_dying.png",1,1},
  {"enemies/plant_dying.png",1,1},
  {"enemies/scorpion_dying.png",1,1},
  {"ui/Brightness.png",1,1},
  {"ui/fade.png",1,1},



  {"icons/capibara.png",1,1}
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

