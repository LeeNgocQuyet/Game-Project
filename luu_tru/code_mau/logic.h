#ifndef _LOGIC__H
#define _LOGIC__H
#include <iostream>
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include "defs.h"
#include "graphics.h"
#include "structs.h"
#include "calculate.h"
#include "animation_frame.h"
#include "clip.h"

void initPlayer(Entity& player) {
    player.x = 400;
    player.y = 300;
    player.health = 20;
    player.side = SIDE_PLAYER;
    player.reload = 0;
}

struct Game {
    bool replay=0;
    Entity player;
    list<Entity*> rangeEnemy;
    list<Entity*> meleeEnemy;
    list<Entity*> bullets;
    list<Entity*> enemyBullets;
    list<Entity*> slashes;
	list<Entity*> fighters;

	SDL_Surface* health_bar = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0xFF000000, 0x00FF0000, 0x000000FF, 0xFF000000);
	int healthPercent = 1;
    int redLength = (healthPercent * SCREEN_WIDTH);


    double elapsedTime = 0;
    Uint32 pauseTime =0;
    Uint32 delta=0;
    int minutes ,seconds ;

    animation slime;
    animation idle;
    animation run;
    animation getHit;
    animation dead;
    animation* status= &idle;

    TTF_Font* font;

    SDL_Texture *background,*bulletTexture, *enemyTexture,*enemy_2Texture, *enemyBulletTexture,*enemySlashTexture,
    *idleTexture,*runTexture,*getHitTexture,*deadTexture,*Idle,*Run,*GetHit,*Dead,*slimeMove,*slimeTexture;
    Mix_Chunk *fireBulletSound,*slashSound,*enemyBulletSound,*deadMusic,*movingSound,*takeDamge ;

    int enemySpawnTimer;
    int stageResetTimer;

    int backgroundX = 0;

    void empty(list<Entity*>& entities) {
        while (!entities.empty()) {
            Entity* e = entities.front();
            entities.pop_front();

        }
    }
    void reset()
    {
        empty(rangeEnemy);
        empty(meleeEnemy);
        empty(bullets);
        empty(enemyBullets);
        empty(slashes);
        meleeEnemy.push_back(&player);
        rangeEnemy.push_back(&player);
	    initPlayer(player);
        enemySpawnTimer = 0;
        stageResetTimer = 90;
	}

    void init(Graphics& graphics)
    {
        //khởi tạo hình ảnh, animation , âm thanh

        player.texture = graphics.loadTexture("img/ship.png");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
        enemyTexture = graphics.loadTexture("img/enemy.png");
        enemy_2Texture = graphics.loadTexture("img/ship.png");

        bulletTexture = graphics.loadTexture("img/tinyBlackBox.png");
        enemySlashTexture = graphics.loadTexture("img/slash.png");
        enemyBulletTexture = graphics.loadTexture("img/enemyBullet.png");
        background = graphics.loadTexture("img/background.jpg");

        slimeMove = graphics.loadTexture(SLIME_FILE);
        slimeTexture = graphics.loadTexture(SLIME_FILE);
        slime.init(slimeTexture, SLIME_FRAMES, SLIME_CLIPS);

        Idle = graphics.loadTexture(IDLE_SPRITE_FILE);
        idleTexture = graphics.loadTexture(IDLE_SPRITE_FILE);
        idle.init(idleTexture, IDLE_FRAMES, IDLE_CLIPS);

        Run = graphics.loadTexture(RUN_SPRITE_FILE);
        runTexture = graphics.loadTexture(RUN_SPRITE_FILE);
        run.init(runTexture, RUN_FRAMES, RUN_CLIPS);

        GetHit = graphics.loadTexture(GETHIT_SPRITE_FILE);
        getHitTexture = graphics.loadTexture(GETHIT_SPRITE_FILE);
        getHit.init(getHitTexture, GETHIT_FRAMES, GETHIT_CLIPS);

        Dead = graphics.loadTexture(DEAD_SPRITE_FILE);
        deadTexture = graphics.loadTexture(DEAD_SPRITE_FILE);
        dead.init(deadTexture, DEAD_FRAMES, DEAD_CLIPS);

        //initAnimation();
        fireBulletSound = Mix_LoadWAV("assets\\bulletSound.wav");
        slashSound = Mix_LoadWAV("assets\\slashSound.wav");
        enemyBulletSound = Mix_LoadWAV("assets\\enemyBulletSound.wav");
        deadMusic = Mix_LoadWAV("assets\\deadSound.wav");
        movingSound = Mix_LoadWAV("assets\\movingSound.wav");
        takeDamge = Mix_LoadWAV("assets\\takeDamge.wav");

        font = graphics.loadFont("assets/Atop-R99O3.ttf", 100);


        reset();
    }

    void fireBullet(int mouseX,int mouseY)
    {
        Entity *bullet = new Entity();
        bullets.push_back(bullet);

        bullet->x = player.x;
        bullet->y = player.y;
        bullet->y += (player.h / 2) - (bullet->h / 2);
        bullet->health = 1;
        bullet->texture = bulletTexture;
        bullet->side = SIDE_PLAYER;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

        calcSlope(mouseX, mouseY,player.x + (player.w / 2), player.y + (player.h / 2),
                   &bullet->dx, &bullet->dy);
        bullet->dx *= ENEMY_BULLET_SPEED;
        bullet->dy *= ENEMY_BULLET_SPEED;

        player.reload = PLAYER_RELOAD;
    }



    void fireEnemyBullet(Entity* enemy)
    {
        Entity *bullet = new Entity();
        enemyBullets.push_back(bullet);

        bullet->x = enemy->x;
        bullet->y = enemy->y;
        bullet->health = 1;
        bullet->texture = enemyBulletTexture;
        bullet->side = SIDE_ENEMY;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

        bullet->x += (enemy->w / 2) - (bullet->w / 2);
        bullet->y += (enemy->h / 2) - (bullet->h / 2);

        calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &bullet->dx, &bullet->dy);
        bullet->dx *= ENEMY_BULLET_SPEED;
        bullet->dy *= ENEMY_BULLET_SPEED;

        enemy->reload = (rand() % FRAME_PER_SECOND * 2);
        Mix_PlayChannel(-1,enemyBulletSound,0);
    }

    void doEnemySlash(Entity* enemy)
    {
        Entity *slash = new Entity();
        slashes.push_back(slash);

        slash->x = enemy->x;
        slash->y = enemy->y;
        slash->health = 1;
        slash->texture = enemySlashTexture;
        slash->side = SIDE_ENEMY;
        SDL_QueryTexture(slash->texture, NULL, NULL, &slash->w, &slash->h);

        slash->x += (enemy->w / 2) - (slash->w / 2);
        slash->y += (enemy->h / 2) - (slash->h / 2);

        enemy->reload = 120;
        Mix_PlayChannel(-1,slashSound,0);

    }

    void doPlayer(int keyboard[],bool mouseButtonDown,int mouseX,int mouseY)
    {
        if (player.health <= 0) return;
        player.dx = player.dy = 0;

        if (player.reload > 0) player.reload--;
        if (keyboard[SDL_SCANCODE_UP]) player.dy = -PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_DOWN]) player.dy = PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_LEFT]) {player.dx = -PLAYER_SPEED;player.turnleft=false;}
        if (keyboard[SDL_SCANCODE_RIGHT]) {player.dx = PLAYER_SPEED;player.turnleft=true;}
        if (mouseButtonDown && player.reload == 0) {fireBullet(mouseX,mouseY);Mix_PlayChannel(-1,fireBulletSound,0);};

        if (!player.isMoving()) status = &idle;
        else {status = &run;}
    }

    bool slashHitFighter(Entity *b)
    {
        if (player.collides(b)&&player.ImmunityDamage==0){
            player.health -= 1;
            status=&getHit;
            player.ImmunityDamage=100;
            Mix_PlayChannel(-1,takeDamge,0);
            return true;
        }
        return false;
    }

    bool bulletHitPlayer(Entity *b)
    {
            if (player.side != b->side
                && b->collides(&player)&&player.ImmunityDamage==0) {
                player.health -= 1;
                status=&getHit;
                player.ImmunityDamage=100;
                Mix_PlayChannel(-1,takeDamge,0);
                return true;
            }
        return false;
    }

    bool bulletHitEnemy(Entity *b)
    {
        for (Entity* enemy: rangeEnemy) {
            if (enemy != &player)
            if (enemy->side != b->side && b->collides(enemy)) {
                enemy->health -= 1;
                return true;
            }
        }
        for (Entity* enemy: meleeEnemy) {
            if (enemy != &player)
            if (enemy->side != b->side && b->collides(enemy)) {
                enemy->health -= 1;
                return true;
            }
        }
        return false;
    }


    void doSlash(void)
    {
        auto it = slashes.begin();
        while (it != slashes.end()) {
            auto temp = it++;
            Entity* b = *temp;
            b->existence();
            if (b->timeExist<0) {
                delete b;
                slashes.erase(temp);
            }
            else
            if (slashHitFighter(b) ) {
                delete b;
                status=&getHit;
                slashes.erase(temp);
            }
        }
    }

    void doEnemyBullets(void)
    {
        auto it = enemyBullets.begin();
        while (it != enemyBullets.end()) {
            auto temp = it++;
            Entity* b = *temp;
            b->move();
            if (bulletHitPlayer(b)) {
                status=&getHit;
                delete b;
                enemyBullets.erase(temp);
            }
            if ( b->offScreen()){
                delete b;
                enemyBullets.erase(temp);
            }
        }
    }
    void doPlayerBullets(void)
    {
        auto it = bullets.begin();
        while (it != bullets.end()) {
            auto temp = it++;
            Entity* b = *temp;
            b->move();
            if (bulletHitEnemy(b) || b->offScreen()) {
                delete b;
                bullets.erase(temp);

            }
        }
    }

    void doEnemies() {
        for (Entity* e: meleeEnemy) {
            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  e->x, e->y, &e->dx, &e->dy);
            //if (e!=&player) e->setTurnLeft(player);
            if (e != &player && player.health != 0 && --e->reload <= 0){
                doEnemySlash(e);
            }
        }
        for (Entity* e: rangeEnemy) {
            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  e->x, e->y, &e->dx, &e->dy);

            if (e != &player && player.health != 0 && --e->reload <= 0){
                fireEnemyBullet(e);
            }
        }

    }
//thêm hiện thị quái sắp xuất hiện
    void spawnEnemies(void) {

        if (--enemySpawnTimer <= 0) {
            Entity *enemy = new Entity();
            meleeEnemy.push_back(enemy);


            enemy->x = rand() % (SCREEN_WIDTH-100);
            enemy->y = rand() % (SCREEN_HEIGHT-100);

            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &enemy->dx, &enemy->dy);
            enemy->dx *= 4;
            enemy->dy *= 4;

            enemy->health = 1;
            enemy->reload = FRAME_PER_SECOND * (1 + (rand() % 3));
            enemy->side = SIDE_ENEMY;
            enemy->texture = enemyTexture;
            SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

            enemySpawnTimer = 100 + rand()%60;

        }
    }
    void spawnEnemies_2(void) {

        if (--enemySpawnTimer <= 0) {
            Entity *enemy = new Entity();
            rangeEnemy.push_back(enemy);


            enemy->x = rand() % (SCREEN_WIDTH-200);
            enemy->y = rand() % (SCREEN_HEIGHT-200);

            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &enemy->dx, &enemy->dy);
            enemy->dx *= 4;
            enemy->dy *= 4;

            enemy->health = 1;
            enemy->reload = FRAME_PER_SECOND * (1 + (rand() % 3));
            enemy->side = SIDE_ENEMY;
            enemy->texture = enemyTexture;
            SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

            enemySpawnTimer = 100 + rand()%60;

        }
    }

    void doFighters(void)
    {
        auto it = rangeEnemy.begin();
        it++;

        while (it != rangeEnemy.end()) {
            auto temp = it++;
            Entity* e = *temp;
            e->move();
            if (e->health == 0) {
                delete e;
                fighters.erase(temp);
                continue;
            }
        }
        auto itt = meleeEnemy.begin();
        itt++;

        while (itt != meleeEnemy.end()) {
            auto temp = itt++;
            Entity* e = *temp;
            e->move();
            if (e->health == 0) {
                delete e;
                fighters.erase(temp);
                continue;
            }
        }
        player.move();
        if (player.x < 0) player.x = 0;
        else if (player.x >= SCREEN_WIDTH - player.w)
            player.x = SCREEN_WIDTH - player.w;
        if (player.y < 0) player.y = 0;
        else if (player.y >= SCREEN_HEIGHT - player.h)
            player.y = SCREEN_HEIGHT - player.h;
	}
    void spawnAllEnemies(void){
        spawnEnemies();
        spawnEnemies_2();
    }
	void doBackground(void) {
        if (--backgroundX < -SCREEN_WIDTH)
        {
            backgroundX = 0;
        }
    }
    void doLogic(int keyboard[],bool mouseButtonDown,int mouseX,int mouseY) {
        if (player.health <= 0) {stageResetTimer--;replay=1;}
        doBackground();
        doPlayer(keyboard,mouseButtonDown,mouseX,mouseY);//thực hiện nhập sự kiện bàn phím/chuột
        doFighters();//thực hiện tấn công di chuyển của quái vật và nhân vật
        doEnemies();// điều chỉnh hướng di chuyển quái vật
        doEnemyBullets();
        doSlash();
        doPlayerBullets();
        spawnAllEnemies();
    }
    void drawBackground(SDL_Renderer* renderer) {
        SDL_Rect dest;
        for (int x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH) {
            dest.x = x;
            dest.y = 0;
            dest.w = SCREEN_WIDTH;
            dest.h = SCREEN_HEIGHT;

            SDL_RenderCopy(renderer, background, NULL, &dest);
        }
    }
    void drawHPBar(Graphics graphics, Entity* character, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255); // màu đen
    SDL_Rect borderRect = {x, y, width+1, height};
    SDL_RenderDrawRect(graphics.renderer, &borderRect);

      // Vẽ phần HP còn lại bên trong thanh
    int hpWidth = (character->health * width) / maxHealth; // phần hp còn lại

    SDL_SetRenderDrawColor(graphics.renderer, 255, 0, 0, 255); // màu đỏ
    SDL_Rect hpRect = {x + 1, y + 1, hpWidth - 1, height - 2};
    SDL_RenderFillRect(graphics.renderer, &hpRect);
    }

    void drawTime(Graphics& graphics ,char timeString[],int minutes,int seconds){
        SDL_Surface* timeSurface = TTF_RenderText_Solid(font, timeString, {255, 255, 255});
        SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(graphics.renderer, timeSurface);
        SDL_Rect timeRect = {300, 0, 200, 100};
        SDL_UpdateTexture(timeTexture, NULL, &timeRect, 0);
        SDL_RenderCopyEx(graphics.renderer, timeTexture, NULL, &timeRect,0,NULL,SDL_FLIP_NONE);
        SDL_FreeSurface(timeSurface);
        SDL_DestroyTexture(timeTexture);
    }
    void draw(Graphics& graphics)
    {
        //drawBackground(graphics.renderer);

        SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;
        SDL_RenderCopy(graphics.renderer, background, NULL, &dest);
        graphics.renderer;
        if (player.health>0)
        {
            drawHPBar(graphics,&player,0,0,200,20);
            elapsedTime = (SDL_GetTicks()-delta)/1000;

            minutes = (int)elapsedTime / 60;
            seconds = (int)elapsedTime % 60;
            char timeString[10];
            sprintf(timeString, "%02d:%02d", minutes, seconds);
            drawTime(graphics,timeString,minutes,seconds);

            slime.slimetick();
            if (player.ImmunityDamage>0) player.ImmunityDamage--;
            for (Entity* b: rangeEnemy)
                if (b->health > 0)
                {
                    if (b!= &player) {//graphics.renderTexture(b->texture, b->x, b->y);
                        b->setTurnLeft(player);
                        graphics.render(b->x,b->y,slime,b->turnleft);
                        }
                    else {

                        graphics.render(player.x,player.y,*status,player.turnleft);
                        status->tick();
                    }
                }
            for (Entity* b: meleeEnemy)
                if (b->health > 0)
                {
                    if (b!= &player) graphics.renderTexture(b->texture, b->x, b->y);

                }
            for (Entity* b: bullets)
                graphics.renderTexture(b->texture, b->x, b->y);
            for (Entity* b: enemyBullets)
                graphics.renderTexture(b->texture, b->x, b->y);

            for (Entity* b: slashes)
                graphics.renderTexture(b->texture, b->x, b->y);

        }

        else {
            if (status!=&dead)Mix_PlayChannel(-1,deadMusic,0);
            status=&dead;
            status->tick();
            graphics.render(player.x,player.y,*status,0);

        }
        //SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255);
        //SDL_RenderClear(graphics.renderer);
    }

};

#endif // _LOGIC__H

