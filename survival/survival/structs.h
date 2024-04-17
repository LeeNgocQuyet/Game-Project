#ifndef _structs__H
#define _structs__H
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

using namespace std;

struct Entity {
	int x;
	int y;
	int w;
	int h;
    float dx;
	float dy;
	int side;
	int health;
	int reload;
	SDL_Texture *texture;

	bool collides(Entity* other) {
	    return (max(x, other->x) < min(x + w, other->x + other->w))
	        && (max(y, other->y) < min(y + h, other->y + other->h));
	}

	void move() {
	    x += dx;
	    y += dy;
	}

	bool offScreen() {
	     return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
	}
};


#endif
