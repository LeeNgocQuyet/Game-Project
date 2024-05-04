#ifndef _menu__h
#define _menu__h
#include <SDL_ttf.h>
#include "graphics.h"

class Menu{
public:
    Menu(const char* name,const int x,const int y): name(name),x(x),y(y){};
    const char* name;
    const int x, y;
    TTF_Font* font = nullptr;

    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* nameTexture = nullptr;
    void init(Graphics graphics) {
        this->font = graphics.loadFont("assets/Purisa-BoldOblique.ttf", 100);
        this->color = {255, 255, 0, 0};
        this->nameTexture = graphics.renderText(this->name, this->font, this->color);
    }
    void render(Graphics graphics){
        graphics.renderTexture(nameTexture,x,y);
    }
};

#endif
