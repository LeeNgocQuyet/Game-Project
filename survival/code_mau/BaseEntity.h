#ifndef _BaseEntity__H
#define _BaseEntity__H

#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <SDL_render.h>
#include "defs.h"

using namespace std;

class BaseEntity {
protected:
  int x, y;
  int w, h;
  float dx;
  float dy;
  SDL_Texture *texture;

public:
  // Constructor declaration
  BaseEntity(int x, int y, int w, int h, float dx, float dy, SDL_Texture *texture);
    void setBaseEntity(int x,int y,int w,int h,float dx, float dy,SDL_Texture *texture);
  // Function declarations
  virtual void move();
  bool collides(BaseEntity* other);
  bool offScreen();
  virtual ~BaseEntity() = default; // Use default destructor

  // Derived class declarations

};
class Player : public BaseEntity {
protected:
  int health;
  int reload;
  int side;

public:
  Player(int health, int reload) : BaseEntity(x, y, w, h, dx, dy, texture), health(health), reload(reload), side(SIDE_PLAYER) {}
};
class Enemy : public BaseEntity {
protected:
  int health;
  int reload;
  int side;

public:
  Enemy(int health, int reload) : BaseEntity(x, y, w, h, dx, dy, texture), health(health), reload(reload), side(SIDE_ENEMY) {}
};
#endif
