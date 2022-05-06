#pragma once

#include "State.h"
#include "../UI/Buttons/Start.h"

class MenuState : public State {
    Texture* backgroundTexture;
    Texture* titleTexture;
    Texture* selectorTexture;

    const double buttonW = 300, buttonH = 140;
    const int titleW = 700, titleH = 258;

    int currentSelection = 0; // boton seleccionado (en el array buttonsUI)

public:

    MenuState(Game* game); 
    ~MenuState() { backgroundTexture = nullptr; };
    void update() override;
    void draw() override;
    void next() override;
    void registerCommands() override;
    void onEnterState() override {};

    void moveBox(Vector2D<int> i) override;
    inline Button* getCurrentButton() override { return buttonsUI[currentSelection]; };

    string getStateName() const override {
        return "Menu state";
    };
};