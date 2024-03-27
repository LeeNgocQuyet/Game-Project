#ifndef _SCREEN__H
#define _SCREEN__H


const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const char* WINDOW_TITLE = "dungeon";
const char* BG = "img\\background.png";
const char* CHARACTOR = "img\\charactor.png";
const char* MONSTER = "img\\monster.png";


const char* MAN_SPRITE_FILE = "img\\_Jump.png";
const int MAN_CLIPS[][4] = {
    {  45,43 ,23,  37},
    { 165, 43, 23, 37},
    { 285, 43, 23, 37}};

int MAN_FRAMES = sizeof(MAN_CLIPS)/sizeof(int)/4;

const char* RUN_SPRITE_FILE = "img\\_Run.png";
int RUN_CLIPS[][4]={
    {  45,43 ,23,  37},
    { 165, 43, 23, 37},
    { 285, 43, 23, 37},
    {  405,43 ,23,  37},
    { 525, 43, 23, 37},

    { 645, 43, 23, 37},
    {  765,43 ,23,  37},
    { 885, 43, 23, 37},
    { 1005, 43, 23, 37},
    {  1125,43 ,23,  37}};
int RUN_FRAMES = sizeof(RUN_CLIPS)/sizeof(int)/10;

int main(){
for (int i=0;i<10;i++){
    int a=45;
    RUN_CLIPS[i][0]=a+i*120;
    RUN_CLIPS[i][1]=43;
    RUN_CLIPS[i][2]=23;
    RUN_CLIPS[i][3]=37;
    }
    return 0;
}

#endif
