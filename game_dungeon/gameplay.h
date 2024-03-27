#ifndef _gameplay__H
#define _gameplay__H
#include <bits/stdc++.h>
const float GRAVITY = -10;

float calculateGravityForce(float mass) {
  return mass * GRAVITY;
}

void updatePosition(float& x, float& y, float velocity, float dt) {
  y += velocity * dt;
  velocity += GRAVITY * dt;
}

void goUp(float &x,float &y,float jump_force){
    y-=jump_force;
}
void goDown(float &x,float &y){
    y+=10;
}
void goLeft(float &x,float &y,float speed){
    x-=speed;
}
void goRight(float &x,float &y,float speed){
    x+=speed;
}
void fallByGravity(float &x,float &y,float &h_ground){
    float dt=0.5;
    if (y<h_ground) {
        y-=dt*GRAVITY;
    }
    if (y>h_ground) y=h_ground;

}
// change game and monster to 1 struct like object.
/*)
struct game{

    bool is_end_game=0;
    bool end_game(){
        if (is_end_game==1) return 1;
        else return 0;
    }

    void KeyPressed()
    {
        SDL_Event event;
        bool quit;
        while (SDL_PollEvent(&event)) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) if(y==h_ground) goUp(x,y,jump_force);
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) goDown(x,y);
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) goLeft(x,y,speed);
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) goRight(x,y,speed);
            if ((event.type == SDL_QUIT) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )) is_end_game=1;
            break;
        }
    }
};
*/


struct object{
    int hp,atk,def;
    float range_attack;
    float x=900, y=300,h_ground=300;
    float x_left,x_right;
    bool left_right=1;
    float speed,jump_force;
    bool is_dead=0;
    object (int _hp,int _atk,int _def,int _range_attack,float _x,float _y,float _h_ground,bool _left_right,float _speed,float _jump_force){
        hp=_hp;
        atk=_atk;
        def=_def;
        range_attack=_range_attack;
        x=_x;
        y=_y;
        h_ground=_h_ground;
        x_left=x-100;
        x_right=x+100;
        left_right=_left_right;
        speed=_speed;
        jump_force=_jump_force;

    }
    void KeyPressed()
    {
        SDL_Event event;
        bool quit;
        while (SDL_PollEvent(&event)) {
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) if(y==h_ground) goUp(x,y,jump_force);
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) goDown(x,y);
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) goLeft(x,y,speed);
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) goRight(x,y,speed);
            if ((event.type == SDL_QUIT) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE )) is_dead=1;
            break;
        }
    }

    void auto_move(float &x,float &y,bool &left_right){
        if (x-speed <= x_left) left_right=1;
        if (x+speed >= x_right) left_right=0;
        if (left_right) {
            x+=speed;
        }
        else {
            x-=speed;
        }
    }
};
bool isInRange(object mon_1,object mon_2){
    int dx = mon_1.x - mon_2.x;
    int dy = mon_1.y - mon_2.y;
    int distance = sqrt(dx * dx + dy * dy);
    return distance <= mon_1.range_attack;
}

void attack(object &obj1,object &obj2){
    obj2.hp-=obj1.atk-obj2.def;
    if (obj2.hp<=0) obj2.is_dead=1;
}

#endif
