#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "screen.h"
#include "graphics.h"
#include "gameplay.h"
#include "render.h"

using namespace std;

SDL_Renderer *renderer;
SDL_Window *window;

SDL_Surface *g_screen = NULL;
SDL_Surface *g_bkground = NULL;
SDL_Event g_even;

SDL_Surface* LoadImage(const char* filename) {
    return SDL_LoadBMP(filename);
}


int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    SDL_Texture* g_bkground  = graphics.loadTexture("background.png");
    SDL_Texture* i_charactor = graphics.loadTexture("charactor.png");
    SDL_Texture* monster_1 = graphics.loadTexture("monster.png");
    SDL_Texture* monster_2 = graphics.loadTexture("monster.png");

    Sprite man;
    Sprite *animation= &man;
    SDL_Texture* manTexture = graphics.loadTexture(MAN_SPRITE_FILE);
    man.init(manTexture, MAN_FRAMES, MAN_CLIPS);

    Sprite run;
    SDL_Texture* runTexture = graphics.loadTexture(RUN_SPRITE_FILE);
    run.init(runTexture, RUN_FRAMES, RUN_CLIPS);


     //xóa phông nền với màu (0,255,255)
    SDL_Surface* image = IMG_Load("charactor.png");
    Uint32 backgroundColor = SDL_MapRGB(image->format,0,255,255);
    SDL_SetColorKey(image, SDL_TRUE, backgroundColor);

    SDL_Texture* s_charactor = SDL_CreateTextureFromSurface(graphics.renderer, image);

    object charactor(200,50,20,60,300,300,300,0,20,100);
    object mon_1(100,20,10,60,500,300,300,1,20,50);
    object mon_2(100,20,10,60,800,300,300,0,20,50);

    do{
        while (SDL_PollEvent(&g_even)) {
            if (g_even.key.keysym.scancode == SDL_SCANCODE_UP) if(charactor.y==charactor.h_ground) {goUp(charactor.x,charactor.y,charactor.jump_force);animation=&man;}
            //if (g_even.key.keysym.scancode == SDL_SCANCODE_DOWN) goDown(charactor.x,charactor.y);
            if (g_even.key.keysym.scancode == SDL_SCANCODE_LEFT) goLeft(charactor.x,charactor.y,charactor.speed);
            if (g_even.key.keysym.scancode == SDL_SCANCODE_RIGHT) goRight(charactor.x,charactor.y,charactor.speed);
            if ((g_even.type == SDL_QUIT) || (g_even.key.keysym.scancode == SDL_SCANCODE_ESCAPE )) charactor.is_dead=1;
            break;
        }
        if(charactor.y==charactor.h_ground)
            animation = &run;
        if (isInRange(charactor,mon_1)) attack(charactor,mon_1);
        if (isInRange(charactor,mon_2)) attack(charactor,mon_2);
        Render(mon_1,mon_2,charactor,graphics,g_bkground,monster_1,monster_2,i_charactor,g_even,*animation);
    }while (charactor.is_dead!=1);

    graphics.quit();
    return 0;
}


