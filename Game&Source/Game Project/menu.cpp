#include "menu.h"
void Menu::init(Graphics graphics,int size) {
    this->font = graphics.loadFont("assets/Atop-R99O3.ttf", size);
    this->color = {255, 255, 0, 0};
    this->nameTexture = graphics.renderText(this->name, this->font, this->color);
    int textWidth, textHeight;
    TTF_SizeText(font, name, &textWidth, &textHeight);

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = textWidth;
    this->rect.h = textHeight;
}
void Menu::render(Graphics graphics){
    graphics.renderTexture(nameTexture,x,y);
}
bool Menu::isClicked(int mouseX,int mouseY){
    SDL_GetMouseState(&mouseX, &mouseY);

    return (mouseX >= rect.x && mouseX < (rect.x + rect.w) &&
            mouseY >= rect.y && mouseY < (rect.y + rect.h));
}
