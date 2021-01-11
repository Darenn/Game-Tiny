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

    Invader() {
      sprite = ssd1306_createSprite(0, 0, sizeof(heartImage),  heartImage);
      sprite.x = 0;
      sprite.y = 0;
      isDead = false;
    }

    Invader(int type, int posX, int posY) {
      sprite = ssd1306_createSprite(posX, posY, sizeof(heartImage),  heartImage);
      sprite.x = posX;
      sprite.y = posY;
      isDead = false;
    }

    void draw() {
      sprite.eraseTrace();
      sprite.draw();
      //ssd1306_drawSpriteEx(sprite.x, sprite.y, sizeof(heartImage),  heartImage);
    }

    void kill() {
      isDead = true;
      sprite.erase();
    }

    void getPosX(uint_fast8_t idx, uint_fast8_t turn) {
      return idx*10 + turn*10;
    }
};

#endif
