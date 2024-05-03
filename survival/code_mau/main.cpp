#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "input.h"
#include "graphics.h"
#include "logic.h"
#include "BaseEntity.h"
#include <ctime>

using namespace std;


int main(int argc, char *argv[]) {
    SDL_Texture *a;

    Enemy e(100,10);
    e.setBaseEntity(1,2,3,4,5,6,a);
    cout<<e.x;
    return 0;
}

