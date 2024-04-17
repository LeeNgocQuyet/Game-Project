#ifndef _SCREEN__H
#define _SCREEN__H


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const char* WINDOW_TITLE = "dungeon";
const char* BG = "img\\Background.png";
const char* CHARACTOR = "img\\charactor.png";
const char* MONSTER = "img\\monster.png";


const char* JUMP_SPRITE_FILE = "img\\_Jump.png";
const int JUMP_CLIPS[][4] = {
    {  45, 43 ,23,  37},
    { 165, 43, 23, 37},
    { 285, 43, 23, 37}};

int JUMP_FRAMES = sizeof(JUMP_CLIPS)/sizeof(int)/4;

const char* RUN_SPRITE_FILE = "img\\_Run.png";
int RUN_CLIPS[][4]={
    {  42,42 , 29,  38},
    { 162, 42, 29, 38},
    { 282, 42, 29, 38},
    { 402, 42, 29, 38},
    { 522, 42, 29, 38},
    { 642 , 42, 29, 38},
    { 762 , 42,29,  38},
    { 882 , 42, 29, 38},
    { 1002, 42, 29, 38},
    { 1122, 42,29,  38}};
int RUN_FRAMES = sizeof(RUN_CLIPS)/sizeof(int)/10;

const char* IDLE_SPRITE_FILE = "img\\_Idle.png";

int IDLE_CLIPS[10][4];
int IDLE_FRAMES = sizeof(IDLE_CLIPS)/sizeof(int)/10;


#endif
