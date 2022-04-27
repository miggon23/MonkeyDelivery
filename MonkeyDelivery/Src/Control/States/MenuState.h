#pragma once

#include "State.h"
#include "../UI/Buttons/Start.h"

class MenuState : public State {
    Texture* backgroundTexture;
    Texture* titleTexture;
    Texture* selectorTexture;

    const double buttonW = 300, buttonH = 140;
    const int titleW = 700, titleH = 258;
    const int selectorW = 300, selectorH = 140;
    int selectorY, selectorX;
    const int selectorInc = buttonH; // el valor debe ser la separacion entre botones

    int currentSelection = 0; // boton seleccionado (en el array buttonsUI)

public:

    MenuState(Game* game); 
    ~MenuState() { backgroundTexture = nullptr; };
    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;
    void onEnterState() override;

    void moveBox(int i);
    inline Button* getCurrentButton() { return buttonsUI[currentSelection]; };

    string getStateName() const override {
        return "Menu state";
    };
};