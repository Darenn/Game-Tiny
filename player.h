#ifndef PLAYER_H
#define PLAYER_H

#include "input.h"
#include "ssd1306.h"

class Player {

  public:
    float speed = 1; // in pixel per 16ms
    float posX = 128/2;
    float posY = 64/2;
    SPRITE sprite;
    
    Player()
    {
      sprite = ssd1306_createSprite(posX, posY, sizeof(heartImage),  heartImage);
    }
  
    void update(){
      move();
      shoot();
    }
  
    void draw() { 
      if(sprite.x != posX || sprite.y != posY) {
        sprite.x = round(posX);
        sprite.y = round(posY);
        sprite.eraseTrace();
        sprite.draw();
      }
    }
  
    void move() {
      if (get_button_pressed(DPAD_RIGHT)) {
        posX += speed;
        note(1, 3);
      } else if (get_button_pressed(DPAD_DOWN)) {
        posY += speed;
        note(2, 3);
      } else if (get_button_pressed(DPAD_LEFT)) {
        posX -= speed;
        note(3, 3);
      } else if (get_button_pressed(DPAD_UP)) {
        posY -= speed;
        note(4, 3);
      }
    }
  
    void shoot() {
      speed = 1;
      if (get_button_pressed(BUTTON_ACTION)) {
        speed = 3;
      }
      if (get_button_pressed(BUTTON_B)) {
        posX = 128/2;
        posY = 64/2;
      }
    }
};
#endif
