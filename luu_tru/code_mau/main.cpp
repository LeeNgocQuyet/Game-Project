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
    input.init();

    Game game;
    game.init(graphics);
    input.get();
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

    while (input.mouseButtonDown==0){

        input.get();

    }
    //MenuEnd
    SDL_Delay(1000);
    while (1)
	{

		graphics.prepareScene();

		input.get();

		game.doLogic(input.keyboard,input.mouseButtonDown,input.mouseX,input.mouseY);
        game.draw(graphics);

		graphics.presentScene();

		SDL_Delay(20);

	}

    return 0;
}




