
#include <iostream>
#include <box2d/box2d.h>
#include "SDL.h"
#include <ctime>

#include "Src/Logic/Game.h"
#include "Src/Control/ViewController.h"
#include "Src/Logic/InputManager.h"


using namespace std;

int main(int argc, char* argv[]) {

    std::cout << "Monkey Delivery, by MoonKey Games" << endl;

    srand(time(NULL));
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try {
        Game* game = new Game("Monkey Delivery", 1800, 1000);
        ViewController controller(game);
       /* InputManager manager(game);
        manager.run();*/
        controller.run();
        delete game; 
        controller.~ViewController();
        /*manager.~InputManager();*/
    }
    catch (const string& e) {
        cout << e;
    }

    return 0;
}

