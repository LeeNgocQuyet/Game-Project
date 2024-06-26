#include <SDL.h>
#include "defs.h"
#include "structs.h"
// sự kiện bàn phím và chuột
struct Input {
    int keyboard[MAX_KEYBOARD_KEYS] = {0};
    bool mouseButtonDown=0;
    int mouseX=100;
    int mouseY=100;
    bool isPaused=false;
	void init()
    {
        for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) keyboard[i] = 0;
    }

    void get() {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyboard[event.key.keysym.scancode] = 1;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) isPaused=!isPaused;
                    break;

                case SDL_KEYUP:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyboard[event.key.keysym.scancode] = 0;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                     mouseButtonDown=1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseButtonDown=0;
                    break;

                default:
                    break;
            }
        }
    }
};
