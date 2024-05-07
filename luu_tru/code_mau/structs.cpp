#include "structs.h"

void Entity::setTurnLeft(Entity& other){
    if (other.x < this->x) {
    this->turnleft = true;
  } if  (other.x > this->x)
    this->turnleft = false;
}

