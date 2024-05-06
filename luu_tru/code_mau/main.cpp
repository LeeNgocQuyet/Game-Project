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
    //MenuBegin

    Menu play("play",100,100);
    Menu setting("setting",100,200);
    Menu quit("quit",100,300);
    play.init(graphics);
    setting.init(graphics);
    quit.init(graphics);

    play.render(graphics);
    setting.render(graphics);
    quit.render(graphics);
    graphics.presentScene();
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
                    while (game.stageResetTimer>0)
                    {

                        graphics.prepareScene();

                        input.get();

                        game.doLogic(input.keyboard,input.mouseButtonDown,input.mouseX,input.mouseY);
                        game.draw(graphics);

                        graphics.presentScene();

                        SDL_Delay(20);

                    }


                } else if (setting.isClicked(mouseX, mouseY)) {
                    cout<<"2";
                } else if (quit.isClicked(mouseX, mouseY)) {
                    cout<<"3";
                    isRunning = false;
                }
                break;
        }
        play.render(graphics);
        setting.render(graphics);
        quit.render(graphics);
        graphics.presentScene();
    }
    SDL_Quit();
    //MenuEnd
    SDL_Delay(1000);


    return 0;
}




