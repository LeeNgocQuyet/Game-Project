#ifndef _LOGIC__H
#define _LOGIC__H
#include <iostream>
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "structs.h"
#include "calculate.h"
#include "animation_frame.h"
#include "clip.h"

void initPlayer(Entity& player) {
    player.x = 400;
    player.y = 300;
    player.health = 1;
    player.side = SIDE_PLAYER;
    player.reload = 0;
}



struct Game {
    //type player;

    Entity player;
    list<Entity*> rangeEnemy;
    list<Entity*> meleeEnemy;
    list<Entity*> bullets;
    list<Entity*> slashes;
	list<Entity*> fighters;
    //list<Entity*> explosions;
    animation idle;
    animation run;
    animation getHit;
    animation dead;

    //void initAnimation(){
        idle.Frames = 4;
        idle.calc();
    //}



    SDL_Texture *bulletTexture, *enemyTexture,*enemy_2Texture, *enemyBulletTexture,*enemySlashTexture,
    *background, *explosionTexture,*idleTexture,*Idle,*Run,*GetHit,*Dead;
    int enemySpawnTimer;
    int stageResetTimer;

    int backgroundX = 0;

    void empty(list<Entity*>& entities) {
        while (!entities.empty()) {
            Entity* e = entities.front();
            entities.pop_front();
            if (e != &player) delete e;
        }
    }
    void reset()
    {
        empty(rangeEnemy);
        empty(meleeEnemy);
        empty(fighters);
        empty(bullets);
        empty(slashes);
        //empty(explosions);
        fighters.push_back(&player);
        meleeEnemy.push_back(&player);
        rangeEnemy.push_back(&player);
	    initPlayer(player);
        enemySpawnTimer = 0;
        stageResetTimer = FRAME_PER_SECOND * 3;
	}

    void init(Graphics& graphics)
    {
        player.texture = graphics.loadTexture("img/ship.png");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
        enemyTexture = graphics.loadTexture("img/enemy.png");
        enemy_2Texture = graphics.loadTexture("img/ship.png");

        bulletTexture = graphics.loadTexture("img/tinyBlackBox.png");
        enemySlashTexture = graphics.loadTexture("img/slash.png");
        enemyBulletTexture = graphics.loadTexture("img/enemyBullet.png");
        background = graphics.loadTexture("img/bikiniBottom.jpg");
        explosionTexture = graphics.loadTexture("img/pngegg.png");

        Idle = graphics.loadTexture(IDLE_SPRITE_FILE);
        idleTexture = graphics.loadTexture(IDLE_SPRITE_FILE);
        idle.init(idleTexture, IDLE_FRAMES, IDLE_CLIPS);
        /*
        Run = graphics.loadTexture(Run_SPRITE_FILE);
        RunTexture = graphics.loadTexture(Run_SPRITE_FILE);
        Run.init(RunTexture, Run_FRAMES, Run_CLIPS);

        Idle = graphics.loadTexture(IDLE_SPRITE_FILE);
        RunTexture = graphics.loadTexture(IDLE_SPRITE_FILE);
        Run.init(idleTexture, IDLE_FRAMES, IDLE_CLIPS);

        Idle = graphics.loadTexture(IDLE_SPRITE_FILE);
        idleTexture = graphics.loadTexture(IDLE_SPRITE_FILE);
        idle.init(idleTexture, IDLE_FRAMES, IDLE_CLIPS);
        //initAnimation();
        */
        reset();
    }

    void fireBullet()
    {
        Entity *bullet = new Entity();
        bullets.push_back(bullet);

        bullet->x = player.x;
        bullet->y = player.y;
        bullet->y += (player.h / 2) - (bullet->h / 2);
        bullet->dx = PLAYER_BULLET_SPEED;
        bullet->health = 1;
        bullet->texture = bulletTexture;
        bullet->side = SIDE_PLAYER;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

        player.reload = PLAYER_RELOAD;
    }



    void fireEnemyBullet(Entity* enemy)
    {
        Entity *bullet = new Entity();
        bullets.push_back(bullet);

        bullet->x = enemy->x;
        bullet->y = enemy->y;
        bullet->health = 1;
        bullet->texture = bulletTexture;
        bullet->side = SIDE_ALIEN;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

        bullet->x += (enemy->w / 2) - (bullet->w / 2);
        bullet->y += (enemy->h / 2) - (bullet->h / 2);

        calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &bullet->dx, &bullet->dy);
        bullet->dx *= ENEMY_BULLET_SPEED;
        bullet->dy *= ENEMY_BULLET_SPEED;

        enemy->reload = (rand() % FRAME_PER_SECOND * 2);
    }

    void doEnemySlash(Entity* enemy)
    {
        Entity *slash = new Entity();
        slashes.push_back(slash);

        slash->x = enemy->x;
        slash->y = enemy->y;
        slash->health = 1;
        slash->texture = enemySlashTexture;
        slash->side = SIDE_ALIEN;
        SDL_QueryTexture(slash->texture, NULL, NULL, &slash->w, &slash->h);

        slash->x += (enemy->w / 2) - (slash->w / 2);
        slash->y += (enemy->h / 2) - (slash->h / 2);

        enemy->reload = 120;
    }

    void doPlayer(int keyboard[])
    {
        if (player.health <= 0) return;

        player.dx = player.dy = 0;

        if (player.reload > 0) player.reload--;
        if (keyboard[SDL_SCANCODE_UP]) player.dy = -PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_DOWN]) player.dy = PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_LEFT]) player.dx = -PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_RIGHT]) player.dx = PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_LCTRL] && player.reload == 0) fireBullet();
    }

    bool slashHitFighter(Entity *b)
    {
        for (Entity* meleeEnemy: meleeEnemy) {
            if (meleeEnemy->side != b->side && b->collides(meleeEnemy)) {
                meleeEnemy->health = 0;
                return true;
            }
        }
        return false;
    }

    bool bulletHitFighter(Entity *b)
    {
        for (Entity* rangeEnemy: rangeEnemy) {
            if (rangeEnemy->side != b->side && b->collides(rangeEnemy)) {
                rangeEnemy->health = 0;
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
            if (slashHitFighter(b) || b->offScreen()) {
                delete b;
                slashes.erase(temp);
            }
        }
    }

    void doBullets(void)
    {
        auto it = bullets.begin();
        while (it != bullets.end()) {
            auto temp = it++;
            Entity* b = *temp;
            b->move();
            if (bulletHitFighter(b) || b->offScreen()) {
                delete b;
                bullets.erase(temp);
            }
        }
    }

    void doEnemies() {
        for (Entity* e: meleeEnemy) {
            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  e->x, e->y, &e->dx, &e->dy);
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
            fighters.push_back(enemy);


            enemy->x = rand() % SCREEN_WIDTH;
            enemy->y = rand() % SCREEN_HEIGHT;

            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &enemy->dx, &enemy->dy);
            enemy->dx *= 4;
            enemy->dy *= 4;

            enemy->health = 1;
            enemy->reload = FRAME_PER_SECOND * (1 + (rand() % 3));
            enemy->side = SIDE_ALIEN;
            enemy->texture = enemyTexture;
            SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

            enemySpawnTimer = 120 + (rand() % 60);
        }
    }
    void spawnEnemies_2(void) {

        if (--enemySpawnTimer <= 0) {
            Entity *enemy = new Entity();
            rangeEnemy.push_back(enemy);
            fighters.push_back(enemy);
            //thêm hiện thị quái sắp xuất hiện

            enemy->x = rand() % SCREEN_WIDTH;
            enemy->y = rand() % SCREEN_HEIGHT;

            calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &enemy->dx, &enemy->dy);
            enemy->dx *= 4;
            enemy->dy *= 4;

            enemy->health = 1;
            enemy->reload = FRAME_PER_SECOND * (1 + (rand() % 3));
            enemy->side = SIDE_ALIEN;
            enemy->texture = enemy_2Texture;
            SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

            enemySpawnTimer = 120 + (rand() % 60);
        }
    }

    void doFighters(void)
    {
        auto it = fighters.begin();
        it++;

        while (it != fighters.end()) {
            auto temp = it++;
            Entity* fighter = *temp;
            fighter->move();
            if (fighter->health == 0) {
                delete fighter;
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
    void doLogic(int keyboard[]) {
        doBackground();
        if (player.health == 0 )//&& --stageResetTimer <= 0)
            reset();
        doPlayer(keyboard);
        doFighters();
        doEnemies();
        doBullets();
        doSlash();
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
        static int i=0;
        for (Entity* b: fighters)
            if (b->health > 0)
            {
                if (b!= &player) graphics.renderTexture(b->texture, b->x, b->y);
                else {
                    if (i==3) {idle.tick();i=0;}
                    i=i+1;
                    graphics.render(player.x,player.y,idle);
                }
            }


        for (Entity* b: bullets)
            graphics.renderTexture(b->texture, b->x, b->y);

        for (Entity* b: slashes)
            graphics.renderTexture(b->texture, b->x, b->y);
        graphics.renderTexture(Idle,100,100);

    }

};

#endif // _LOGIC__H

