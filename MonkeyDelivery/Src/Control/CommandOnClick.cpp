#include "CommandOnClick.h"
#include "../Control/UI/Sliders/Slider.h"
#include "../Control/States/State.h"
#include "../Control/UI/Sliders/SliderClick.h"
CommandOnClick::~CommandOnClick(){
    if (sliderClicked_ != nullptr) {
        sliderClicked_->onCursorCollision();
    }
    sliderClicked_ = nullptr;
}
bool CommandOnClick::parse(SDL_Event& event){
    if (event.type == SDL_MOUSEBUTTONDOWN)         
        return true;
    
    if (sliderClicked_ != nullptr) { sliderClicked_->onCursorCollision(); sliderClicked_ = nullptr; }
    return false;
}

void CommandOnClick::execute(){
    if (sliderClicked_!=nullptr&&!sliderClicked_->onClick()) {
        sliderClicked_->onCursorCollision();
        sliderClicked_ = nullptr;
    }
    //else if (sliderClicked == nullptr) {
        for (auto it : game->getState()->getSlidersUI()) {

            if (it->getSliderClick()->onClick()) {
                it->getSliderClick()->onCursorCollision();
                sliderClicked_ = it->getSliderClick();
                break;
            }
        }
    //}  
}
