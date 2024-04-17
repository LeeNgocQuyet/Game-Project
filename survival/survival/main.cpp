#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "input.h"
#include "structs.h"
#include "logic.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
    Graphics graphics;
    graphics.init();
    Input input;
    input.init();
    Game game;
    game.init(graphics);

    while (1)
	{
		graphics.prepareScene();

		input.get();

		game.doLogic(input.keyboard);
        game.draw(graphics);

		graphics.presentScene();

		SDL_Delay(10);
	}

    graphics.quit();
    return 0;
}
