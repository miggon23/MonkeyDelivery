
#include <iostream>
#include <box2d/box2d.h>
#include "SDL.h"


//#include "Logic/Game.h"
//#include "Control/ViewController.h"

using namespace std;

int main(int argc, char* argv[]) {

    srand(time(NULL));
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try {
        //Game* game = new Game("Car game 1.0", 800, 320, 5000);
        //ViewController controller(game);
        //controller.run();
        //delete game;
    }
    catch (const string& e) {
        cout << e;
    }

    return 0;
}

