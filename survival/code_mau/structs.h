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

class animation : public Sprite{
public:
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};
class Entity {//:type{
public:
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
	SDL_Texture *texture;

	bool collides(Entity* other) {
	    return (max(x, other->x) < min(x + w, other->x + other->w))
	        && (max(y, other->y) < min(y + h, other->y + other->h));
	}

	void move() {
	    x += dx;
	    y += dy;
	}
	void existence(){
        timeExist--;
	}

	bool offScreen() {
	     return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
	}
};

#endif // _APP__H