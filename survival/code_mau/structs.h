#ifndef _APP__H
#define _APP__H
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <cmath>
#include <vector>

using namespace std;


class Sprite {
public :
    int Frames;
    vector <vector<int>> Clips;

    vector <int> coordinates;

    void calc(){
        coordinates.push_back(0);
        coordinates.push_back(0);
        coordinates.push_back(20);
        coordinates.push_back(20);
        for (int i=0;i<Frames;i++){
            coordinates[0]=i*20;
            Clips.push_back(coordinates);
        }
    }
};

class animation {
public:
     SDL_Texture * texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames,const  int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            this->clips.push_back(clip);
        }
    }
    void tick() {
        static int i=0;
        i--;
        if (i<=0) {i=3;
        currentFrame = (currentFrame + 1) % clips.size();}
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};





#endif // _APP__H
