#ifndef UFO_H
#define UFO_H

#include "invader.h"
#include "player.h"

#define UFO_START_POSITION_X 0
#define UFO_START_POSITION_Y 8

#define TIME_BETWEEN_UFO_MAX 30 * 30 // in frame
#define TIME_BETWEEN_UFO_MIN 30 * 15 // in frame
#define UFO_SPEED 1 // in pixel per frame

static SPRITE UFO = ssd1306_createSprite(0, UFO_START_POSITION_Y, sizeof(ufoBMP),  ufoBMP);

static bool launched = false;
static bool activated = false;
static uint_fast8_t timeUntilNextUFO;

void launchUFO() {
 launched = true;
 UFO.x = UFO_START_POSITION_X;
}

void activateUFO() {
  activated = true;
  launchUFO();
}

void killUFO() {
  launched = false;
  UFO.erase();
  timeUntilNextUFO = GT_RANDOM_RANGE(TIME_BETWEEN_UFO_MIN, TIME_BETWEEN_UFO_MAX);
}

void updateUFO() {
  static uint_fast8_t timer = 0;  
  
  if(diveCounter < 1) return;
  if(!activated) activateUFO();
  debugDisplayInt(999, 0, 50);
  
  if(launched) {
    debugDisplayInt(333, 0, 50);
    //delay(1000);
    if(UFO.x > 127) { // gone off screen
      debugDisplayInt(777, 0, 50);
      //delay(1000);
      killUFO();
    } else {
      UFO.x += UFO_SPEED;
      UFO.eraseTrace();
      UFO.draw();
    }  
  } 
  else if(timer >= timeUntilNextUFO) {
    debugDisplayInt(444, 0, 50);
    //delay(1000);
    timer=0;
    launchUFO();
  } 
  else {
    debugDisplayInt(555, 0, 50);
    ++timer;
  }
}

// Make a function for both  player and UFO?
static bool processCollisionWithUFO() {
  Rect ufoRect = Rect{UFO.x, UFO.y, UFO.x + 8, UFO.y + 8};
  if (isColliding(getBulletRect(&p.bullet), ufoRect)) {
    p.bullet.sprite.x = p.sprite.x; // To draw the explosion on the UFO position
    p.bullet.sprite.y = p.sprite.y;
    kill(&p.bullet);
    killUFO();
  }
}

#endif
