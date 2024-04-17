#ifndef _clip_h
#define _clip_H


const char* IDLE_SPRITE_FILE = "img/idle.png";
int IDLE_CLIPS[][4] ={
    {  0, 0, 20, 20},
    { 20, 0, 20, 20},
    {40, 0, 20, 20},
    {60, 0, 20, 20}};

int IDLE_FRAMES = sizeof(IDLE_CLIPS)/sizeof(int)/4;
#endif // _clip_h
