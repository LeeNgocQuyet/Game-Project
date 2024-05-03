#ifndef _BaseEntity__H
#define _BaseEntity__H

class BaseEntity {
protected:
    int x, y;
    int w, h;
    float dx;
	float dy;
    SDL_Texture *texture;

public:
    BaseEntity(int x, int y, int w, int h,float dx,float dy,SDL_Texture *texture)
        : x(x), y(y), w(w), h(h),dx(dx),dy(dy) ,texture(texture) {}

    // Hàm xử lý
    void move() {
	    x += dx;
	    y += dy;
	}
	bool collides(BaseEntity* other) {
	    return (max(x, other->x) < min(x + w, other->x + other->w))
	        && (max(y, other->y) < min(y + h, other->y + other->h));
	}
	bool offScreen() {
	     return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
	}
    virtual ~BaseEntity() {}
};

class Player : public BaseEntity {
protected:
    int health;
    int reload;
    int side;

public:
    Player(int health,int reload) :BaseEntity(x, y, w, h, dx, dy, texture), health(health) , reload(reload), side(SIDE_PLAYER){}
    // Hàm xử lý

};
class Enemy : public BaseEntity {
protected:
    int health;
    int reload;
    int side;

public:
    Enemy(int health,int reload,int side) :BaseEntity(x, y, w, h, dx, dy, texture), health(health) , reload(reload), side(SIDE_ENEMY){}
    // Hàm xử lý

};
#endif
