#ifndef _render__H
#define _render__H
#include "screen.h"
#include "graphics.h"
#include "gameplay.h"

void Render(object &mon_1,object &mon_2,object &charactor,Graphics &graphics,SDL_Texture* g_bkground,SDL_Texture* monster_1,SDL_Texture* monster_2,SDL_Texture* i_charactor,SDL_Event &event
            ,Sprite &man){


        mon_1.auto_move(mon_1.x,mon_1.y,mon_1.left_right);
        mon_2.auto_move(mon_2.x,mon_2.y,mon_2.left_right);

        graphics.prepareScene(g_bkground);

        if (!mon_1.is_dead)
            graphics.renderTexture(graphics.renderer,monster_1,mon_1.x,mon_1.y,pic_width,pic_height);
        if (!mon_2.is_dead)
            graphics.renderTexture(graphics.renderer,monster_2,mon_2.x,mon_2.y,pic_width,pic_height);
        man.tick();
        graphics.render(charactor.x,charactor.y,man);
        //charactor.KeyPressed();
        graphics.presentScene();

        //rơi tự do

        fallByGravity(charactor.x,charactor.y,charactor.h_ground);

        //kiểm tra phạm vi tấn công
        SDL_Delay(50);
}

#endif
