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
	plantSS_Yellow,
	plantSS_Red,
	plantSS_Purple,
	plantSS_Orange,
	scorpionSS_Death,
	scorpionSS_Default,

	//5-Items (General) - 18
	Item_Banana,
	Item_Boots01,
	Item_Boots02,
	Item_Boots03,
	Item_Lantern01,
	Item_Package,
	Item_Soda01,
	Item_Soda02,
	Item_pickaxe01,
	Item_pickaxe02,
	Item_Spray,

	//5,2-Items (World)
	lanternCircular,
	lanternDown,
	lanternLeft,
	lanternUp,
	lightGeneric,
	Item_Coins,

	//5,1-Items (Light)
	worldObject_Bed,
	worldObject_blockRock01,
	worldObject_blockRock02,
	worldObject_Chest_Closed,
	worldObject_Chest_Opened,
	worldObject_Gold,
	worldObject_Tutorial,
	worldObject_TutorialComplete,
	worldObject_HappyHippo,
	worldObject_Hierbas,
	worldObject_Pez,
	worldObject_Note,

	//6-Map - 4
	mapMarker,
	mapOverlay,
	minimapOverlay,
	minimapBorder,
	playerIconTex,
	minimapOverlay02,
	leyendaMapa,

	//7-Missions - 13
	mission_UI_Helper,
	mission_UI_Panel,
	mission_UI_Selector,
	Mission01,
	Mission02,
	Mission03,
	Mission04,
	Mission05,
	Mission06,
	Mission07,
	Mission08,
	Mission09,
	MissionPanel_Interact,

	//8-Monkey SpriteSheets - 3
	monkeySS_Default,
	monkeyTired_Icon,
	monkeyScared_Icon,
	monkeySS_GreenBoots,
	monkeySS_OrangeBoots,

	//9-NPCS SpriteSheets - 10
	npc_Coco,
	npc_Eagle,
	npc_Fish,
	npc_Fox,
	npc_Frog,
	npc_Hipo,
	npc_Pavo,
	npc_Tucan,
	npc_Rabbit,
	npc_Kangaroo,
	npc_Seller,

	//10-Shop - 7
	shop_Banana,
	shop_Boots01,
	shop_Boots02,
	shop_Boots03,
	shop_Soda1,
	shop_Soda2,
	shop_Farol,
	shop_Linterna,
	shop_UI_PanelShop,
	shop_UI_Selector,
	ShopPanel_Interact,
	shop_UI_Controls,
	shop_Items,
	shop_Spray,

	//11-UI Overlay (InGame) - 7
	UI_dialogueBox,
	UI_Coin,
	UI_energyLevel,
	UI_fearLevel,
	UI_InventoryBar,
	UI_InventoryBarOverlay,
	UI_InventorySelector,
	UI_playerHUD,
	UI_playerHUD_BackFill,
	UI_timer,
	fearPopUp,
	coinPopUp,
	enerPopUp,

	//12-UI Overlay (InGame Buffs) - 3
	UI_energyBuff,
	UI_fearBuff,
	UI_speedBuff,
	UI_speedDebuff,

	//13-UI Overlay (Menu) - 21
	UI_Black,
	UI_Brightness,
	button_Back,
	button_Continue,
	button_Main_Credits,
	button_Main_ExitButton,
	button_Main_Options,
	button_Main_StartButton,
	button_Pause,
	button_Selector,
	UI_Fade,
	UI_label,
	UI_Checker00,
	UI_Checker01,
	UI_Checker02,
	UI_Checker03,
	UI_MissionsControls,
	UI_Controls,

	missingTex,
	transitionTex,
	overlay,

	coco_Icon,
	eagle_Icon,
	fish_Icon,
	frog_Icon,
	hipo_Icon,
	pavo_Icon,
	rabit_Icon,
	tucan_Icon,
	fox_Icon,

	// Cinematica
	frame001,
	frame002,
	frame003,
	frame004,
	frame005,
	frame006,
	frame007,
	frame008,
	frame009,
	frame010,
	frame011,
	frame012,
	frame013,
	frame014,
	frame015,
	frame016,
	frame017,
	frame018,
	frame019,
	frame020,
	frame021,
	frame022,
	frame023,
	frame024,
	frame025,
	frame026,
	frame027,
	frame028,
	frame029,
	frame030,
	frame031,
	frame032,
	frame033,
	frame034,
	frame035,
	frame036,
	frame037,
	frame038,
	frame039,
	frame040,
	frame041,
	frame042,
	frame043,
	frame044,
	frame045,
	frame046,
	frame047,
	frame048,
	frame049,
	frame050,
	frame051,
	frame052,
	frame053,
	frame054,
	frame055,
	frame056,
	frame057,
	frame058,
	frame059,
	frame060,
	frame061,
	frame062,
	frame063,
	frame064,
	frame065,
	frame066,
	frame067,
	frame068,
	frame069,
	frame070,
	frame071,
	frame072,
	frame073,
	frame074,
	frame075,
	frame076,
	frame077,
	frame078,
	frame079,
	frame080,
	frame081,
	frame082,
	frame083

};

const int NUM_TEXTURES = 234;

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
	{"enemies/plantSS_Yellow.png",1,1},
	{"enemies/plantSS_Red.png",1,1},
	{"enemies/plantSS_Purple.png",1,1},
	{"enemies/plantSS_Orange.png",1,1},
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
	{"items/Item_pickaxe01.png",1,1},
	{"items/Item_pickaxe02.png",1,1},
	{"items/Item_Spray.png",1,1},

	//Items Light
	{"items/light/lanternCircular.png",1,1},
	{"items/light/lanternDown.png",1,1},
	{"items/light/lanternLeft.png",1,1},
	{"items/light/lanternUp.png",1,1},
	{"items/light/lightGeneric.png",1,1},

	//Items World
	{"items/world/Item_Coins.png",1,1},
	{"items/world/worldObject_Bed.png",1,1},
	{"items/world/worldObject_blockRock01.png",1,1},
	{"items/world/worldObject_blockRock02.png",1,1},
	{"items/world/worldObject_Chest_Closed.png",1,1},
	{"items/world/worldObject_Chest_Opened.png",1,1},
	{"items/world/worldObject_Gold.png",1,1},
	{"items/world/worldObject_Tutorial.png",1,1},
	{"items/world/worldObject_TutorialDone.png",1,1},
	{"items/world/Item_HappyHippo.png",1,1},
	{"items/world/Item_Hierbas.png",1,1},
	{"decor/Trohpy_Fish02.png",1,1},
	{"items/world/note.png",1,1},

	//6-Map
	{"map/mapMarker.png",1,1},
	{"map/mapOverlay.png",1,1},
	{"map/minimapOverlay.png",1,1},
	{"map/minimapBorder.png",1,1},
	{"map/playerIcon.png",1,1},
	{"map/minimapOverlay02.png",1,1},
	{"map/leyendaMapa.png",1,1},

	//7-Missions
	{"missions/mission01_UI_Helper.png",1,1},
	{"missions/mission_UI_Panel.png",1,1},
	{"missions/mission_UI_Selector.png",1,1},
	{"missions/Mission01.png",1,1},
	{"missions/Mission02.png",1,1},
	{"missions/Mission03.png",1,1},
	{"missions/Mission04.png",1,1},
	{"missions/Mission05.png",1,1},
	{"missions/Mission06.png",1,1},
	{"missions/Mission07.png",1,1},
	{"missions/Mission08.png",1,1},
	{"missions/Mission09.png",1,1},
	{"missions/MissionPanel_Interact.png",1,1},

	//8-Monkey SpriteSheets
	{"monkeyAnims/monkeySS_Default.png",1,1},
	{"ui/tiredIcon.png",1,1},
	{"ui/scaredIcon.png",1,1},
	{"monkeyAnims/monkeySS_Green_Boots.png",1,1},
	{"monkeyAnims/monkeySS_Orange_Boots.png",1,1},

	//9-NPCS SpriteSheets
	{"npcs/NPC_Coco.png",1,1},
	{"npcs/NPC_Eagle.png",1,1},
	{"npcs/NPC_Fish.png",1,1},
	{"npcs/NPC_Fox.png",1,1},
	{"npcs/NPC_Frog.png",1,1},
	{"npcs/NPC_Hipo.png",1,1},
	{"npcs/NPC_Pavo.png",1,1},
	{"NPCs/NPC_Tucan.png",1,1},
	{"npcs/NPC_Rabbit.png",1,1},
	{"npcs/NPC_Kangaroo.png",1,1},
	{"npcs/NPC_Seller.png",1,1 },

	//10-Shop
	{"shop/shop_Banana.png",1,1},
	{"shop/shop_Boots01.png",1,1},
	{"shop/shop_Boots02.png",1,1},
	{"shop/shop_Boots03.png",1,1},
	{"shop/shop_Soda.png",1,1},
	{"shop/Shop_Soda02.png",1,1},
	{"shop/Shop_Farol.png",1,1},
	{"shop/Shop_Linterna.png",1,1},
	{"shop/shop_UI_PanelShop.png",1,1},
	{"shop/shop_UI_Selector.png",1,1},
	{"shop/ShopPanel_Interact.png",1,1},
	{"shop/shopControls.png",1,1},
	{"shop/items.png",1,1 },
	{ "shop/shop_Spray.png",1,1 },

	//UI Overlay (InGame)
	{"ui/InGame/dialoguebox.png",1,1},
	{"ui/InGame/UI_Coin.png",1,1},
	{"ui/InGame/UI_energyLevel.png",1,1},
	{"ui/InGame/UI_fearLevel.png",1,1},
	{"ui/InGame/UI_InventoryBar.png",1,1},
	{"ui/InGame/UI_InventoryBarOverlay.png",1,1},
	{"ui/InGame/UI_InventorySelector.png",1,1},
	{"ui/InGame/UI_playerHUD.png",1,1},
	{"ui/InGame/UI_playerHUD_BackFill.png",1,1},
	{"ui/InGame/timer.png",1,1},
	{"ui/InGame/fearPopUp.png",1,1},
	{"ui/InGame/coinPopUp.png",1,1},
	{"ui/InGame/enerPopUp.png",1,1},

	//UI Overlay (InGame Buffs)
	{"ui/InGame/UI_energyBuff.png",1,1 },
	{"ui/InGame/UI_fearBuff.png",1,1 },
	{"ui/InGame/UI_speedBuff.png",1,1 },
	{"ui/InGame/UI_speedDebuff.png",1,1 },

	//UI Overlay (Menu)
	{"ui/Menu/black.png",1,1},
	{"ui/Menu/Brightness.png",1,1},
	{"ui/Menu/button_Back.png",1,1 },
	{"ui/Menu/button_Continue.png",1,1 },
	{"ui/Menu/button_Main_Credits.png",1,1 },
	{"ui/Menu/button_Main_ExitButton.png",1,1 },
	{"ui/Menu/button_Main_Options.png",1,1 },
	{"ui/Menu/button_Main_StartButton.png",1,1 },
	{"ui/Menu/button_Pause.png",1,1 },
	{"ui/Menu/button_Selector.png",1,1 },
	{"ui/Menu/fade.png",1,1},
	{"ui/Menu/label.png",1,1},
	{"ui/Menu/UI_Checker00.png",1,1},
	{"ui/Menu/UI_Checker01.png",1,1},
	{"ui/Menu/UI_Checker02.png",1,1},
	{"ui/Menu/UI_Checker03.png",1,1},
	{"ui/controlsmissions.png",1,1},
	{"tutorial/Tutorial.png",1,1},

	{"missingTex.png",1,1},
	{"transition.png",1,1},
	{"overlay.png",1,1},

	{ "ui/cocoIcon.png",1,1 },
	{ "ui/eagleIcon.png",1,1 },
	{ "ui/fishIcon.png",1,1 },
	{ "ui/frogIcon.png",1,1 },
	{ "ui/hipoIcon.png",1,1 },
	{ "ui/pavoIcon.png",1,1 },
	{ "ui/rabitIcon.png",1,1 },
	{ "ui/tucanIcon.png",1,1 },
	{ "ui/foxIcon.png",1,1 },

	// Cinematica final
	{ "cinematic/001.jpg",1,1 },
	{ "cinematic/002.jpg",1,1 },
	{ "cinematic/003.jpg",1,1 },
	{ "cinematic/004.jpg",1,1 },
	{ "cinematic/005.jpg",1,1 },
	{ "cinematic/006.jpg",1,1 },
	{ "cinematic/007.jpg",1,1 },
	{ "cinematic/008.jpg",1,1 },
	{ "cinematic/009.jpg",1,1 },
	{ "cinematic/010.jpg",1,1 },
	{ "cinematic/011.jpg",1,1 },
	{ "cinematic/012.jpg",1,1 },
	{ "cinematic/013.jpg",1,1 },
	{ "cinematic/014.jpg",1,1 },
	{ "cinematic/015.jpg",1,1 },
	{ "cinematic/016.jpg",1,1 },
	{ "cinematic/017.jpg",1,1 },
	{ "cinematic/018.jpg",1,1 },
	{ "cinematic/019.jpg",1,1 },
	{ "cinematic/020.jpg",1,1 },
	{ "cinematic/021.jpg",1,1 },
	{ "cinematic/022.jpg",1,1 },
	{ "cinematic/023.jpg",1,1 },
	{ "cinematic/024.jpg",1,1 },
	{ "cinematic/025.jpg",1,1 },
	{ "cinematic/026.jpg",1,1 },
	{ "cinematic/027.jpg",1,1 },
	{ "cinematic/028.jpg",1,1 },
	{ "cinematic/029.jpg",1,1 },
	{ "cinematic/030.jpg",1,1 },
	{ "cinematic/031.jpg",1,1 },
	{ "cinematic/032.jpg",1,1 },
	{ "cinematic/033.jpg",1,1 },
	{ "cinematic/034.jpg",1,1 },
	{ "cinematic/035.jpg",1,1 },
	{ "cinematic/036.jpg",1,1 },
	{ "cinematic/037.jpg",1,1 },
	{ "cinematic/038.jpg",1,1 },
	{ "cinematic/039.jpg",1,1 },
	{ "cinematic/040.jpg",1,1 },
	{ "cinematic/041.jpg",1,1 },
	{ "cinematic/042.jpg",1,1 },
	{ "cinematic/043.jpg",1,1 },
	{ "cinematic/044.jpg",1,1 },
	{ "cinematic/045.jpg",1,1 },
	{ "cinematic/046.jpg",1,1 },
	{ "cinematic/047.jpg",1,1 },
	{ "cinematic/048.jpg",1,1 },
	{ "cinematic/049.jpg",1,1 },
	{ "cinematic/050.jpg",1,1 },
	{ "cinematic/051.jpg",1,1 },
	{ "cinematic/052.jpg",1,1 },
	{ "cinematic/053.jpg",1,1 },
	{ "cinematic/054.jpg",1,1 },
	{ "cinematic/055.jpg",1,1 },
	{ "cinematic/056.jpg",1,1 },
	{ "cinematic/057.jpg",1,1 },
	{ "cinematic/058.jpg",1,1 },
	{ "cinematic/059.jpg",1,1 },
	{ "cinematic/060.jpg",1,1 },
	{ "cinematic/061.jpg",1,1 },
	{ "cinematic/062.jpg",1,1 },
	{ "cinematic/063.jpg",1,1 },
	{ "cinematic/064.jpg",1,1 },
	{ "cinematic/065.jpg",1,1 },
	{ "cinematic/066.jpg",1,1 },
	{ "cinematic/067.jpg",1,1 },
	{ "cinematic/068.jpg",1,1 },
	{ "cinematic/069.jpg",1,1 },
	{ "cinematic/070.jpg",1,1 },
	{ "cinematic/071.jpg",1,1 },
	{ "cinematic/072.jpg",1,1 },
	{ "cinematic/073.jpg",1,1 },
	{ "cinematic/074.jpg",1,1 },
	{ "cinematic/075.jpg",1,1 },
	{ "cinematic/076.jpg",1,1 },
	{ "cinematic/077.jpg",1,1 },
	{ "cinematic/078.jpg",1,1 },
	{ "cinematic/079.jpg",1,1 },
	{ "cinematic/080.jpg",1,1 },
	{ "cinematic/081.jpg",1,1 },
	{ "cinematic/082.jpg",1,1 },
	{ "cinematic/083.jpg",1,1 },
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