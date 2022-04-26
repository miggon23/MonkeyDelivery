#pragma once
#include <array>
#include "Texture.h"
#include <string>

#include <iostream>
#include <vector>

using namespace std;

const string IMAGES_PATH = "Images/";

enum TextureName 
{
	/*
	* Ordenadas por orden de carpetas, y ficheros (alfabetico)
	* Index - Nombre de seccion - Numero de sprites por seccion
	*/

	//1-Background (UI Menu) - 4
		bckg_GameTitle,
		bckg_Image,
		bckg_options,
		bckg_woodWall,
	
	//3-Decorations (House) - 8
		Trohpy_Coco,
		Trohpy_Eagle,
		Trohpy_Fish,
		Trohpy_Fox,
		Trohpy_Frog,
		Trohpy_Hippo,
		Trohpy_Kangaroo,
		Trohpy_Toucan,
	
	//4-Enemies SpritesSheets - 10
		batSS_Death,
		batSS_Default,
		bullSS_Death,
		bullSS_Default,
		catSS_Death,
		catSS_Default,
		plantSS_Death,
		plantSS_Default,
		scorpionSS_Death,
		scorpionSS_Default,
	
	//5-Items (General) - 17
		Item_Banana,
		Item_Boots01,
		Item_Boots02,
		Item_Boots03,
		Item_Lantern01,
		Item_Package,
		Item_Soda01,
		Item_Soda02,

	//5,2-Items (World)
		lanternCircular,
		lanternDown,
		lanternLeft,
		lanternUp,
		lightGeneric,

	//5,1-Items (Light)
		worldObject_Bed,
		worldObject_blockRock01,
		worldObject_Chest_Closed,
		worldObject_Chest_Opened,
		worldObject_Gold,
		worldObject_Tutorial,
	
	//6-Map - 4
		mapMarker,
		mapOverlay,
		minimapOverlay,
		playerIconTex,
	
	//7-Missions - 6
		mission_UI_Helper,
		mission_UI_Panel,
		mission_UI_Selector,
		Mission01,
		Mission02,
		Mission07,
		MissionPanel_Interact,
	
	//8-Monkey SpriteSheets - 3
		monkeySS_Default,
	
	//9-NPCS SpriteSheets - 10
		npc_Coco,
		npc_Eagle,
		npc_Fish,
		npc_Fox,
		npc_Frog,
		npc_Hipo,
		npc_Pavo,
		npc_Tucan,
		npc_Kangaroo,
		npc_Turtle,

	//10-Shop - 6
		shop_Boots01,
		shop_Boots02,
		shop_Boots03,
		shop_Soda,
		shop_UI_PanelShop,
		shop_UI_Selector,
		ShopPanel_Interact,
	
	//11-UI Overlay (InGame) - 7
		UI_dialogueBox,
		UI_Coin,
		UI_energyLevel,
		UI_fearLevel,
		UI_InventoryBar,
		UI_InventoryBarOverlay,
		UI_InventorySelector,
		UI_playerHUD,
	
	//12-UI Overlay (Menu) - 19
		UI_Black,
		UI_Brightness,
		button_Back,
		button_BackMenu,
		button_Continue,
		button_Main_Credits,
		button_Main_ExitButton,
		button_Main_Options,
		button_Main_StartButton,
		button_Options,
		button_Pause,
		UI_Fade,
		UI_label,
		UI_SliderBase,
		UI_SliderClicker,
		UI_Checker00,
		UI_Checker01,
		UI_Checker02,
		UI_Checker03,

		missingTex,
};

const int NUM_TEXTURES = 98;

typedef struct {
	string filename;
	int numRows; int numCols;
} TextureAttributes;


const TextureAttributes TEXTURE_ATTRIBUTES[NUM_TEXTURES] =
{ 
	//1-Background (UI Menu)
	{"background/bckg_GameTitle.png",1,1},
	{"background/bckg_Image.png",1,1},
	{"background/bckg_WoodPanneling.png",1,1},
	{"background/bckg_woodWall.webp",1,1},

	//2-Buttons (UI Menu)
	
	
	//3-Decorations (House)
	{"decor/Trohpy_Coco.png",1,1},
	{"decor/Trohpy_Eagle.png",1,1},
	{"decor/Trohpy_Fish.png",1,1},
	{"decor/Trohpy_Fox.png",1,1},
	{"decor/Trohpy_Frog.png",1,1},
	{"decor/Trohpy_Hippo.png",1,1},
	{"decor/Trohpy_Kangaroo.png",1,1},
	{"decor/Trohpy_Toucan.png",1,1},

	//4-Enemies SpritesSheets
	{"enemies/batSS_Death.png",1,1},
	{"enemies/batSS_Default.png",1,1},
	{"enemies/bullSS_Death.png",1,1},
	{"enemies/bullSS_Default.png",1,1},
	{"enemies/catSS_Death.png",1,1},
	{"enemies/catSS_Default.png",1,1},
	{"enemies/plantSS_Death.png",1,1},
	{"enemies/plantSS_Default.png",1,1},
	{"enemies/scorpionSS_Death.png",1,1},
	{"enemies/scorpionSS_Default.png",1,1},

	//5-Items
	{"items/Item_Banana.png",1,1},
	{"items/Item_Boots01.png",1,1},
	{"items/Item_Boots02.png",1,1},
	{"items/Item_Boots03.png",1,1},
	{"items/Item_Lantern01.png",1,1},
	{"items/Item_Package.png",1,1},
	{"items/Item_Soda01.png",1,1},
	{"items/Item_Soda02.png",1,1},
	
	//Items Light
		{"items/light/lanternCircular.png",1,1},
		{"items/light/lanternDown.png",1,1},
		{"items/light/lanternLeft.png",1,1},
		{"items/light/lanternUp.png",1,1},
		{"items/light/lightGeneric.png",1,1},

	//Items World
		{"items/world/worldObject_Bed.png",1,1},
		{"items/world/worldObject_blockRock01.png",1,1},
		{"items/world/worldObject_Chest_Closed.png",1,1},
		{"items/world/worldObject_Chest_Opened.png",1,1},
		{"items/world/worldObject_Gold.png",1,1},
		{"items/world/worldObject_Tutorial.png",1,1},


	//6-Map
	{"map/mapMarker.png",1,1},
	{"map/mapOverlay.png",1,1},
	{"map/minimapOverlay.png",1,1},
	{"map/playerIcon.png",1,1},

	//7-Missions
	{"missions/mission_UI_Helper.png",1,1},
	{"missions/mission_UI_Panel.png",1,1},
	{"missions/mission_UI_Selector.png",1,1},
	{"missions/Mission01.png",1,1},
	{"missions/Mission02.png",1,1},
	{"missions/Mission07.png",1,1},
	{"missions/MissionPanel_Interact.png",1,1},

	//8-Monkey SpriteSheets
	{"monkeyAnims/monkeySS_Default.png",1,1},

	//9-NPCS SpriteSheets
	{"npcs/NPC_Coco.png",1,1},
	{"npcs/NPC_Eagle.png",1,1},
	{"npcs/NPC_Fish.png",1,1},
	{"npcs/NPC_Fox.png",1,1},
	{"npcs/NPC_Frog.png",1,1},
	{"npcs/NPC_Hipo.png",1,1},
	{"npcs/NPC_Kangaroo.png",1,1},
	{"npcs/NPC_Pavo.png",1,1},
	{"NPCs/NPC_Tucan.png",1,1},
	{"npcs/NPC_Turtle.png",1,1},

	//10-Shop
	{"shop/shop_Boots01.png",1,1},
	{"shop/shop_Boots02.png",1,1},
	{"shop/shop_Boots03.png",1,1},
	{"shop/shop_Soda.png",1,1},
	{"shop/shop_UI_PanelShop.png",1,1},
	{"shop/shop_UI_Selector.png",1,1},
	{"shop/ShopPanel_Interact.png",1,1},

	//UI Overlay (InGame)
	{"ui/InGame/dialoguebox.png",1,1},
	{"ui/InGame/UI_Coin.png",1,1},
	{"ui/InGame/UI_energyLevel.png",1,1},
	{"ui/InGame/UI_fearLevel.png",1,1},
	{"ui/InGame/UI_InventoryBar.png",1,1},
	{"ui/InGame/UI_InventoryBarOverlay.png",1,1},
	{"ui/InGame/UI_InventorySelector.png",1,1},
	{"ui/InGame/UI_playerHUD.png",1,1},

	//UI Overlay (Menu)
	{"ui/Menu/black.png",1,1},
	{"ui/Menu/Brightness.png",1,1},
	{"ui/Menu/button_Back.png",1,1 },
	{"ui/Menu/button_BackMenu.png",1,1 },
	{"ui/Menu/button_Continue.png",1,1 },
	{"ui/Menu/button_Main_Credits.png",1,1 },
	{"ui/Menu/button_Main_ExitButton.png",1,1 },
	{"ui/Menu/button_Main_Options.png",1,1 },
	{"ui/Menu/button_Main_StartButton.png",1,1 },
	{"ui/Menu/button_Options.png",1,1 },
	{"ui/Menu/button_Pause.png",1,1 },
	{"ui/Menu/fade.png",1,1},
	{"ui/Menu/label.png",1,1},
	{"ui/Menu/sliderBase.png",1,1},
	{"ui/Menu/sliderClicker.png",1,1},
	{"ui/Menu/UI_Checker00.png",1,1},
	{"ui/Menu/UI_Checker01.png",1,1},
	{"ui/Menu/UI_Checker02.png",1,1},
	{"ui/Menu/UI_Checker03.png",1,1},
	{"missingTex.png",1,1},


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

	Texture* getTexture(TextureName name) const 
	{
		return textures[name];
	};
};