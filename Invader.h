#ifndef INVADER_H
#define INVADER_H

#include "ssd1306.h"

#define INVADER_0 0
#define INVADER_1 1
#define INVADER_2 2

class Invader {
  
  public:
    SPRITE sprite;
    bool isDead;

    Invader(int type, int posX, int posY) {
      sprite = ssd1306_createSprite(posX, posY, sizeof(heartImage),  heartImage);
      sprite.x = posX;
      sprite.y = posY;
      isDead = false;
    }

    void draw() {
      if(!isDead) {
        sprite.eraseTrace();
        sprite.draw();
      }
    }

    void kill() {
      isDead = true;
      sprite.eraseTrace();
    }
};

#endif
