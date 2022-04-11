#include "CommandClick.h"
#include "Button.h"
#include "../Control/UI/Sliders/Slider.h"
#include "../Control/States/State.h"
#include "../Control/UI/Sliders/SliderClick.h"

CommandClick::~CommandClick(){
    if (sliderClicked_ != nullptr) {
        sliderClicked_->onCursorCollision();
    }
    sliderClicked_ = nullptr;
}
bool CommandClick::parse(SDL_Event& event) {
   if (event.type == SDL_MOUSEBUTTONDOWN)     
        return true;
   if (event.type == SDL_MOUSEBUTTONUP) {      
        if (sliderClicked_ != nullptr) { 
            sliderClicked_->onCursorCollision(); 
            sliderClicked_ = nullptr; 
        }
   }
    return false;
}

void CommandClick::execute() {
    if (sliderClicked_ != nullptr && !sliderClicked_->onClick()) {
        sliderClicked_->onCursorCollision();
        sliderClicked_ = nullptr;
    }
    for (auto it : game->getState()->getSlidersUI()) {

        if (it->getSliderClick()->onClick()) {
            it->getSliderClick()->onCursorCollision();
            sliderClicked_ = it->getSliderClick();
            break;
        }
    } 
    for (auto it : game->getState()->getButtonsUI()) {
        if (it->onClick()) {
            //sdlutils().soundEffects().at("click").setVolume(game->getSoundEfectsVolume());
            //sdlutils().soundEffects().at("click").play(0, 1);
            it->onCursorCollision();
            break;
        }
    }
}