#ifndef _menu__h
#define _menu__h
#include <SDL_ttf.h>
#include "graphics.h"
#include <string>
//using namespace std;

class Menu{
public:
    Menu(const char* name,const int x,const int y): name(name),x(x),y(y){};
    const char* name;
    const int x, y;
    SDL_Rect rect;

    bool Clicked=0;
    TTF_Font* font = nullptr;

    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* nameTexture = nullptr;
    void init(Graphics graphics,int size) ;
    void render(Graphics graphics);
    bool isClicked(int mouseX,int mouseY);
};




#endif
