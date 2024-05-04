#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "input.h"
#include "graphics.h"
#include "logic.h"
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

    while (1)
	{
		graphics.prepareScene();

		input.get();

		game.doLogic(input.keyboard,input.mouseButtonDown,input.mouseX,input.mouseY);
        game.draw(graphics);

		graphics.presentScene();

		SDL_Delay(20);
	}

    graphics.quit();
    return 0;
}




