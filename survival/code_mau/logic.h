#ifndef _LOGIC__H
#define _LOGIC__H

#include "BaseEntity.h"
#include <vector>
#include <string>
class Level {
public:
    Level();

    ~Level();

private:
    int multi=1;
    string background = "map 1";
    vector<BaseEntity*> enemy;
};
class EventManager {
public:
  EventManager();

  ~EventManager();

  void Update(){}


private:
  //SDL_Event event;
};



#endif
