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
	mission3Texture,
	mission4Texture,
	cama,
	dialogoPrueba,
	bullTexture,
	monkeyspritesheet,
	monkeyspritesheetPirate,
	batspritesheet,
	bullspritesheet,
	catspritesheet,
	startButtonTexture,
	scorpionSpritesheet,
	shopTexture,
	shopPanel,
	missionSelector,
	shopSelector,
	plantSpritesheet,
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
	shop_Soda,
	shop_Boots01,
	shop_Boots02,
};


const int NUM_TEXTURES = 46;



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
  {"NPCs/NPC_Tucan.png",1,1},
  {"catPrueba.png",1,1},
  {"batPrueba.png",1,1},
  {"missions/Mision1.png",1,1},
  {"missions/Mision2.png",1,1},
  {"missions/Mision2.png",1,1},
  {"missions/Mision2.png",1,1},
  {"decorations/bed.png",1,1},
  {"ui/dialoguebox.png",1,1},
  {"bull.png",1,1},
  {"animaciones mono/monkeySpriteSheett.png",1,1},
  {"animaciones mono/monkeySpriteSheetPirate.png",1,1},
  {"enemies/bat.png",1,1},
  {"enemies/bull.png",1,1},
  {"enemies/cat.png",1,1},
  {"Buttons/startButton.png",1,1},
  {"enemies/scorpion.png",1,1},
  {"shop/transparent.png",1,1},
  {"shop/panelShop.png",1,1},
  {"shop/missionSelector.png",1,1},
  {"shop/shop_Selector.png",1,1},
  {"enemies/plant.png",1,1},
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
  {"objects/Shop_Soda.png",1,1},
  {"objects/Shop_Boots01.png",1,1},
  {"objects/Shop_Boots02.png",1,1},
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

