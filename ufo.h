#ifndef UFO_H
#define UFO_H

#include "invader.h"
#include "player.h"

#define UFO_START_POSITION_X 0
#define UFO_START_POSITION_Y 8

#define TIME_BETWEEN_UFO_MAX 30 * 20 // in frame
#define TIME_BETWEEN_UFO_MIN 30 * 10 // in frame
#define UFO_SPEED 1 // in pixel per frame

static SPRITE UFO = ssd1306_createSprite(0, UFO_START_POSITION_Y, sizeof(ufoBMP),  ufoBMP);

static bool launched = false;
static bool activated = false;
static uint_fast16_t timeUntilNextUFO;

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


// Make a function for both  player and UFO?
static bool processCollisionWithUFO() {
  Rect ufoRect = Rect{UFO.x, UFO.y, UFO.x + 8, UFO.y + 8};
  if (isColliding(getBulletRect(&p.bullet), ufoRect)) {
    p.bullet.sprite.x = UFO.x; // To draw the explosion on the UFO position
    p.bullet.sprite.y = UFO_START_POSITION_Y;
    kill(&p.bullet);
    killUFO();
    updateScore(SCORE_UFO_STRONG);
  }
}

void updateUFO() {
  static uint_fast16_t timer = 0;  
  
  if(diveCounter < 1) return;
  if(!activated) activateUFO();
  
  if(launched) {
    if(p.bullet.enabled) processCollisionWithUFO();
    if(UFO.x > 118) { // gone on screen limit
      killUFO();
    } else {
      UFO.x += UFO_SPEED;
      UFO.eraseTrace();
      UFO.draw();
    }  
  } 
  else if(timer >= timeUntilNextUFO) {
    timer=0;
    launchUFO();
  } 
  else {
    ++timer;
  }
}


#endif
