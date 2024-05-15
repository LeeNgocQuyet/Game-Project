#include <iostream>
#include <SDL.h>

#include "defs.h"
#include "input.h"
#include "graphics.h"
#include "logic.h"
#include "menu.h"
#include "highScore.h"
#include <ctime>

using namespace std;
bool handleEvents(bool &paused) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        return false;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          paused = !paused;
        }
        break;
    }
  }

  return true;
}

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
    string highscore = GetHighScoreFromFile("high_score.txt");
    bool showHighScore=0;

    Menu highScore(stringToChar(highscore),100,300);
    Menu replay("replay",100,100);
    Menu Record("Record",100,200);
    Menu quit("quit",100,300);
    Menu pause("press ESC to Continue/Pause",0,200);

    play.init(graphics,100);
    highScore.init(graphics,200);
    replay.init(graphics,100);
    Record.init(graphics,100);
    quit.init(graphics,100);
    pause.init(graphics,50);

    play.render(graphics);
    Record.render(graphics);
    quit.render(graphics);


    SDL_Texture* background = graphics.loadTexture("img/mBackground.jpg");
    SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
    SDL_RenderCopy(graphics.renderer, background, NULL, &dest);

    Uint32 begin_time=0,end_time=0;
    SDL_Event m_event;
    bool isRunning = true;
    bool isPaused = false;
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
                        begin_time=0;
                        end_time=0;
                        game.pauseTime=0;

                        input.get();
                        if (input.isPaused==true){
                             begin_time = SDL_GetTicks();}
                        while (input.isPaused==true){
                            input.get();
                            pause.render(graphics);
                            graphics.presentScene();
                        }
                        end_time=SDL_GetTicks();
                        if (begin_time!=0) game.pauseTime = (end_time- begin_time) ;
                        game.delta+=game.pauseTime;

                        game.doLogic(input.keyboard,input.mouseButtonDown,input.mouseX,input.mouseY);
                        game.draw(graphics);

                        graphics.presentScene();

                        SDL_Delay(20);

                    }
                } else if (Record.isClicked(mouseX, mouseY)) {
                    showHighScore=!showHighScore;
                    SDL_RenderCopy(graphics.renderer, background, NULL, &dest);
                    if (showHighScore) highScore.render(graphics);

                    //graphics.presentScene();

                } else if (quit.isClicked(mouseX, mouseY)) {
                    isRunning = false;
                }
                break;
        }
        UpdateHighScore("high_score.txt", game.score, highscore);
        if (!showHighScore){
            if(game.replay==1) replay.render(graphics);
            else play.render(graphics);

            quit.render(graphics);

        }
        Record.render(graphics);
        graphics.presentScene();
    }
    graphics.quit();
    SDL_Quit();


    return 0;
}




