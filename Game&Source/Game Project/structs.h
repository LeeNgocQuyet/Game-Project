#ifndef _APP__H
#define _APP__H
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <cmath>
#include <vector>

using namespace std;
// chứa animation và Entity của player/Enemy

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
    void slimetick(){
        currentFrame = (currentFrame + 1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};
class Entity {
public:

    int ImmunityDamage=0;
	int x;
	int y;
	int w;
	int h;
    float dx;
	float dy;
	float angle;
	float cos=1,sin=1;
	int side;
	int health;
	int reload;
	int timeExist=10;
	bool turnleft=1;
	SDL_Texture *texture;

	void move();
	bool isMoving();
	void existence(){
        timeExist--;
	}
	bool collides(Entity* other);

	bool offScreen() {
	     return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
	}

    void setTurnLeft(Entity& other);

};



#endif // _APP__H
