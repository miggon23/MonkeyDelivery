#include "GameOverState.h"
#include "../../Player/Player.h"

GameOverState::GameOverState(Game* game) : State(game)
{
	registerCommands();
	textureMap.insert({
		{1, TextureName::frame001},
		{2, TextureName::frame002},
		{3, TextureName::frame003},
		{4, TextureName::frame004},
		{5, TextureName::frame005},
		{6, TextureName::frame006},
		{7, TextureName::frame007},
		{8, TextureName::frame008},
		{9, TextureName::frame009},
		{10, TextureName::frame010},
		{11, TextureName::frame011},
		{12, TextureName::frame012},
		{13, TextureName::frame013},
		{14, TextureName::frame014},
		{15, TextureName::frame015},
		{16, TextureName::frame016},
		{17, TextureName::frame017},
		{18, TextureName::frame018},
		{19, TextureName::frame019},
		{20, TextureName::frame020},
		{21, TextureName::frame021},
		{22, TextureName::frame022},
		{23, TextureName::frame023},
		{24, TextureName::frame024},
		{25, TextureName::frame025},
		{26, TextureName::frame026},
		{27, TextureName::frame027},
		{28, TextureName::frame028},
		{29, TextureName::frame029},
		{30, TextureName::frame030},
		{31, TextureName::frame031},
		{32, TextureName::frame032},
		{33, TextureName::frame033},
		{34, TextureName::frame034},
		{35, TextureName::frame035},
		{36, TextureName::frame036},
		{37, TextureName::frame037},
		{38, TextureName::frame038},
		{39, TextureName::frame039},
		{40, TextureName::frame040},
		{41, TextureName::frame041},
		{42, TextureName::frame042},
		{43, TextureName::frame043},
		{44, TextureName::frame044},
		{45, TextureName::frame045},
		{46, TextureName::frame046},
		{47, TextureName::frame047},
		{48, TextureName::frame048},
		{49, TextureName::frame049},
		{50, TextureName::frame050},
		{51, TextureName::frame051},
		{52, TextureName::frame052},
		{53, TextureName::frame053},
		{54, TextureName::frame054},
		{55, TextureName::frame055},
		{56, TextureName::frame056},
		{57, TextureName::frame057},
		{58, TextureName::frame058},
		{59, TextureName::frame059},
		{60, TextureName::frame060},
		{61, TextureName::frame061},
		{62, TextureName::frame062},
		{63, TextureName::frame063},
		{64, TextureName::frame064},
		{65, TextureName::frame065},
		{66, TextureName::frame066},
		{67, TextureName::frame067},
		{68, TextureName::frame068},
		{69, TextureName::frame069},
		{70, TextureName::frame070},
		{71, TextureName::frame071},
		{72, TextureName::frame072},
		{73, TextureName::frame073},
		{74, TextureName::frame074},
		{75, TextureName::frame075},
		{76, TextureName::frame076},
		{77, TextureName::frame077},
		{78, TextureName::frame078},
		{79, TextureName::frame079},
		{80, TextureName::frame080},
		{81, TextureName::frame081},
		{82, TextureName::frame082},
		{83, TextureName::frame083},

		});
	int i = 1;
	renderCinematic(i);
	/*Uint32 interval = 1000; Uint32 startTicks;
	startTicks = SDL_GetTicks();
	while (i < NUM_ELEMS + 1)
	{
		startTicks = SDL_GetTicks();
		if (startTicks >= interval)
		{
			i++;
			renderCinematic(i);
			startTicks -= interval;
		}
	}*/
}

void GameOverState::renderCinematic(int i)
{
	/*SDL_Rect rectPanel = { 0,0,(int)game->getWindowWidth(), (int)game->getWindowHeight() };

	auto it = textureMap.find(i);
	if (it != textureMap.end())
	{
		game->getTexture(it->second)->render(rectPanel);
	}*/

	game->renderText("GAME OVER", (int)game->getWindowWidth() / 2 - 100, (int)game->getWindowHeight() / 2);
}

void GameOverState::registerCommands() {

}