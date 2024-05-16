#include "structs.h"
void Entity::move() {
    x += dx;
    y += dy;
}
bool Entity::isMoving(){
    if (dx==0&&dy==0) return false;
    return true;
}
bool Entity::collides(Entity* other) {
    return (
        x <= other->x + other->w &&
        x + w >= other->x &&
        y <= other->y + other->h &&
        y + h >= other->y    );
}
void Entity::setTurnLeft(Entity& other){
    if (other.x < this->x) {
    this->turnleft = true;
  } if  (other.x > this->x)
    this->turnleft = false;
}

