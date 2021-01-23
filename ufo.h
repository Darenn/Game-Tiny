#ifndef UFO_H
#define UFO_H

#include "invader.h"
#include "player.h"

#define UFO_START_POSITION_X 0
#define UFO_START_POSITION_Y 8

#define TIME_BETWEEN_UFO_MAX 20 // in seconds
#define TIME_BETWEEN_UFO_MIN 10 // in seconds
#define UFO_SPEED 1 // in pixel per frame

static SPRITE UFO = ssd1306_createSprite(0, UFO_START_POSITION_Y, sizeof(ufoBMP),  ufoBMP);

static struct UfoInfo {
  bool launched:1;
  bool activated:1;
  uint_fast8_t timeUntilNextUFO:6; // can be at 5 if you need
} ufoInfo {false, false, 0};



void launchUFO() {
 ufoInfo.launched = true;
 UFO.x = UFO_START_POSITION_X;
}

void activateUFO() {
  ufoInfo.activated = true;
  launchUFO();
}

void killUFO() {
  ufoInfo.launched = false;
  UFO.erase();
  ufoInfo.timeUntilNextUFO = GT_RANDOM_RANGE(TIME_BETWEEN_UFO_MIN, TIME_BETWEEN_UFO_MAX);
}


// Make a function for both  player and UFO?
static bool processCollisionWithUFO() {
  Rect ufoRect = Rect{UFO.x, UFO.y, UFO.x + 8, UFO.y + 8};
  if (isColliding(getBulletRect(&p.bullet), ufoRect)) {
    p.bullet.sprite.x = UFO.x; // To draw the explosion on the UFO position
    p.bullet.sprite.y = UFO_START_POSITION_Y;
    kill(&p.bullet);
    killUFO();
    updateScore(SCORE_UFO_STRONG);
    return true;
  }
  return false;
}

void updateUFO() {
  static uint_fast16_t timer = 0;  
  
  if(invaderBrain.diveCounter < 1) return;
  if(!ufoInfo.activated) activateUFO();
  
  if(ufoInfo.launched) {
    if(p.bullet.enabled) processCollisionWithUFO();
    if(UFO.x > 118) { // gone on screen limit
      killUFO();
    } else {
      UFO.x += UFO_SPEED;
      UFO.eraseTrace();
      UFO.draw();
    }  
  } 
  else if(timer >= ufoInfo.timeUntilNextUFO*30) {
    timer=0;
    launchUFO();
  } 
  else {
    ++timer;
  }
}


#endif
