#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "input.h"
#include "graphics.h"
#include "logic.h"
#include "menu.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));

    Graphics graphics;
    graphics.init();
    Mix_Music *gMusic = graphics.loadMusic("assets\\backgroundMusic.mp3");
    graphics.play(gMusic);

    Input input;
    Input menuInput;
    menuInput.init();
    input.init();
    Game game;
    game.init(graphics);
    menuInput.init();

    //Menu

    Menu play("play",100,100);
    Menu replay("replay",100,100);
    Menu setting("credit",100,200);
    Menu quit("quit",100,300);
    play.init(graphics);
    replay.init(graphics);
    setting.init(graphics);
    quit.init(graphics);

    play.render(graphics);
    setting.render(graphics);
    quit.render(graphics);

    SDL_Texture* background = graphics.loadTexture("img/mBackground.jpg");
    SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
    SDL_RenderCopy(graphics.renderer, background, NULL, &dest);

    SDL_Event m_event;
    bool isRunning = true;
    while (isRunning) {
        SDL_WaitEvent(&m_event);

        switch (m_event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (play.isClicked(mouseX, mouseY)) {
                    game.reset();
                    while (game.stageResetTimer>0)
                    {
                        graphics.prepareScene();

                        input.get();

                        game.doLogic(input.keyboard,input.mouseButtonDown,input.mouseX,input.mouseY);
                        game.draw(graphics);

                        graphics.presentScene();

                        SDL_Delay(20);

                    }
                    cout<<"1";
                } else if (setting.isClicked(mouseX, mouseY)) {
                    graphics.prepareScene();
                    cout<<"2";

                } else if (quit.isClicked(mouseX, mouseY)) {
                    isRunning = false;
                }
                break;
        }
        if(game.replay==1) replay.render(graphics);
        else play.render(graphics);
        setting.render(graphics);
        quit.render(graphics);
        graphics.presentScene();
    }
    graphics.quit();
    SDL_Quit();


    return 0;
}




