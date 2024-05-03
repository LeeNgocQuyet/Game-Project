#include "BaseEntity.h"

BaseEntity::BaseEntity(int x, int y, int w, int h, float dx, float dy, SDL_Texture *texture)
  : x(x), y(y), w(w), h(h), dx(dx), dy(dy), texture(texture) {}
void setBaseEntity(int _x, int y, int w, int h, float dx, float dy, SDL_Texture *texture){
    x=_x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->dx = dx;
    this->dy = dy;
    this->texture = texture;
}
void BaseEntity::move() {
  x += dx;
  y += dy;
}

bool BaseEntity::collides(BaseEntity* other) {
  return (max(x, other->x) < min(x + w, other->x + other->w))
         && (max(y, other->y) < min(y + h, other->y + other->h));
}

bool BaseEntity::offScreen() {
  return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
}
