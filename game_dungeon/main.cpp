#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "screen.h"
#include "graphics.h"
#include "object.h"
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
    SDL_Texture* g_bkground  = graphics.loadTexture(BG);
    SDL_Texture* i_charactor = graphics.loadTexture(CHARACTOR);
    SDL_Texture* monster_1 = graphics.loadTexture(MONSTER);
    SDL_Texture* monster_2 = graphics.loadTexture(MONSTER);

    Sprite jump;
    Sprite *animation= &jump;
    SDL_Texture* jumpTexture = graphics.loadTexture(JUMP_SPRITE_FILE);
    jump.init(jumpTexture, JUMP_FRAMES, JUMP_CLIPS);

    Sprite run;
    SDL_Texture* runTexture = graphics.loadTexture(RUN_SPRITE_FILE);
    run.init(runTexture, RUN_FRAMES, RUN_CLIPS);

    Sprite idle;
    for (int i=0;i<10;i++){
    IDLE_CLIPS[i][0]= 42+120*i;
    IDLE_CLIPS[i][1]= 42;
    IDLE_CLIPS[i][2]= 29;
    IDLE_CLIPS[i][3]= 38;
    }
    SDL_Texture* idleTexture = graphics.loadTexture(IDLE_SPRITE_FILE);
    idle.init(idleTexture, IDLE_FRAMES, IDLE_CLIPS);
     //xóa phông nền với màu (0,255,255)
    SDL_Surface* image = IMG_Load(CHARACTOR);
    Uint32 backgroundColor = SDL_MapRGB(image->format,0,255,255);
    SDL_SetColorKey(image, SDL_TRUE, backgroundColor);

    SDL_Texture* s_charactor = SDL_CreateTextureFromSurface(graphics.renderer, image);

    object charactor(200,50,20,60,600,510,510,0,20,100);
    object mon_1(100,20,10,60,500,510,510,1,20,50);
    object mon_2(100,20,10,60,800,510,510,0,20,50);
    animation=&idle;
    do{
        while (SDL_PollEvent(&g_even)) {
                while (g_even.type==SDL_KEYDOWN){
            if (g_even.key.keysym.scancode == SDL_SCANCODE_UP) if(charactor.y==charactor.h_ground) {
                goUp(charactor.x,charactor.y,charactor.jump_force);
                animation=&jump;break;
            }
            //if (g_even.key.keysym.scancode == SDL_SCANCODE_DOWN) goDown(charactor.x,charactor.y);
            if (g_even.key.keysym.scancode == SDL_SCANCODE_LEFT) {goLeft(charactor.x,charactor.y,charactor.speed);animation =&run;}
            if (g_even.key.keysym.scancode == SDL_SCANCODE_RIGHT) {goRight(charactor.x,charactor.y,charactor.speed);animation =&run;}
            if ((g_even.type == SDL_QUIT) || (g_even.key.keysym.scancode == SDL_SCANCODE_ESCAPE )) charactor.is_dead=1;
            break;}
            if (g_even.type==SDL_KEYUP) animation=&idle;
        }

        if (isInRange(charactor,mon_1)) attack(charactor,mon_1);
        if (isInRange(charactor,mon_2)) attack(charactor,mon_2);
        Render(mon_1,mon_2,charactor,graphics,g_bkground,monster_1,monster_2,i_charactor,g_even,*animation);
    }while (charactor.is_dead!=1);

    graphics.quit();
    return 0;
}


