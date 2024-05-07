#ifndef _clip_h
#define _clip_H


const char* IDLE_SPRITE_FILE = "img/idle.png";
const int IDLE_CLIPS[][4]
={
    {  0, 0, 20, 20},
    { 20, 0, 20, 20},
    {40, 0, 20, 20},
    {60, 0, 20, 20}};

const int IDLE_FRAMES = sizeof(IDLE_CLIPS)/sizeof(int)/4;

const char* RUN_SPRITE_FILE = "img/run.png";
const int RUN_CLIPS[][4]
={
    {  0, 0, 20, 20},
    { 20, 0, 20, 20},
    {40, 0, 20, 20},
    {60, 0, 20, 20},
    {80, 0, 20, 20},
    {100, 0, 20, 20}};

const int RUN_FRAMES = sizeof(RUN_CLIPS)/sizeof(int)/4;

const char* GETHIT_SPRITE_FILE = "img/getHit.png";
const int GETHIT_CLIPS[][4]
={
    {  0, 0, 20, 20},
    { 20, 0, 20, 20}};

const int GETHIT_FRAMES = sizeof(GETHIT_CLIPS)/sizeof(int)/4;


const char* DEAD_SPRITE_FILE = "img/dead.png";
const int DEAD_CLIPS[][4]
={
    {  0, 0, 20, 20},
    { 20, 0, 20, 20},
    {40, 0, 20, 20},
    {60, 0, 20, 20},
    {80, 0, 20, 20},
    {100, 0, 20, 20}};

const int DEAD_FRAMES = sizeof(DEAD_CLIPS)/sizeof(int)/4;

//slime
const char* SLIME_FILE = "img/slime/slime_move.png";
const int SLIME_CLIPS[][4]
={
    {  0, 0, 32, 25},
    { 32, 0, 32, 25},
    {64, 0, 32, 25},
    {96, 0, 32, 25}};

const int SLIME_FRAMES = sizeof(SLIME_CLIPS)/sizeof(int)/4;
#endif // _clip_h
