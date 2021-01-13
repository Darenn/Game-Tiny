#ifndef INVADER_H
#define INVADER_H

#include "ssd1306.h"

#define INVADER_0 0
#define INVADER_1 1
#define INVADER_2 2

#define XSPACE_BETWEEN_INVADERS 10
#define YSPACE_BETWEEN_INVADERS_ROWS 10
#define INVADER_STRAFE_MOVE_DIST 2
#define INVADER_DIVE_MOVE_DIST 2
#define INVADERS_COUNT_PER_ROW 5 // TODO rename column
#define STARTING_INVADER_X_MOVE_COUNT 15 + 15
#define INVADER_STARTING_X_POSITION 0
#define INVADERS_ROW_COUNT 3
#define INVADERS_COUNT INVADERS_COUNT_PER_ROW * INVADERS_ROW_COUNT
#define INVADER_WIDTH 8

uint_fast8_t invaderXSpeed = 2; // TODO wont change should be define
signed int invaderDirection = 1; // 1 = right and -1 = left

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

    

    void kill() {
      isDead = true;
      sprite.erase();
    }
};

Invader invaders [INVADERS_COUNT];


int getIndexByCoordinates(int row, int col) {
  return col + row * INVADERS_COUNT_PER_ROW;
}

int invaderRightXMoveCount = STARTING_INVADER_X_MOVE_COUNT; // How many time invaders moves on X axis before going down
int invaderLeftXMoveCount = 0; // How many time invaders moves on X axis before going down

int getColumnWithInvaderIndex(int index) {
  return index % INVADERS_COUNT_PER_ROW;
}

int getRowWithInvaderIndex(int index) {
  return index / INVADERS_COUNT_PER_ROW;
}


uint_fast8_t getFirstInvaderAliveCol() {
  for (uint_fast8_t col = 0; col < INVADERS_COUNT_PER_ROW; ++col) {
    for (uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if (!invaders[getIndexByCoordinates(row, col)].isDead) {
        return col;
      }
    }
  }
  return 99;
}

uint_fast8_t getLastInvaderAliveCol() {
  for (uint_fast8_t col = INVADERS_COUNT_PER_ROW - 1; col > 0; --col) {
    for (uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if (!invaders[getIndexByCoordinates(row, col)].isDead) {
        return col;
      }
    }
  }
  return 99;
}

void compensateDead() {
  #define s_leftiestAliveColumn getColumnWithInvaderIndex(getFirstInvaderAliveCol())
  #define s_leftCompensation s_leftiestAliveColumn * (INVADER_WIDTH / invaderXSpeed)
  #define s_rightiestAliveColumn getColumnWithInvaderIndex(getLastInvaderAliveCol())
  #define s_rightCompensation (INVADERS_COUNT_PER_ROW - 1 - s_rightiestAliveColumn) * (INVADER_WIDTH / invaderXSpeed)

  invaderRightXMoveCount = STARTING_INVADER_X_MOVE_COUNT + s_rightCompensation;
  invaderLeftXMoveCount = INVADER_STARTING_X_POSITION - s_leftCompensation;
}

uint_fast8_t invaderCounter = 0; // TODO On each invade call we move only one row for performance

static uint_fast8_t nextinvaderRightXMoveCount = invaderRightXMoveCount;


int getPosX(uint_fast8_t idx, uint_fast8_t strafeCounter, uint_fast8_t diveCounter) {
  int posXStart = getColumnWithInvaderIndex(idx) * XSPACE_BETWEEN_INVADERS;
  int offsetXStrafe =  strafeCounter * INVADER_STRAFE_MOVE_DIST;
  return posXStart + offsetXStrafe;
}

int getPosY(uint_fast8_t idx, uint_fast8_t diveCounter) {
  return getRowWithInvaderIndex(idx) * YSPACE_BETWEEN_INVADERS_ROWS + diveCounter * INVADER_DIVE_MOVE_DIST;
}

void drawInvader(Invader* i, int index, int strafeCounter, int diveCounter) {
      i->sprite.x = getPosX(index, strafeCounter, diveCounter);
      i->sprite.y = getPosY(index, diveCounter);
      i->sprite.eraseTrace();
      i->sprite.draw();
      //ssd1306_drawSpriteEx(getPosX(index, strafeCounter), getPosY(index, diveCounter), sizeof(heartImage),  heartImage); //!!!!! y is in blocks vertical position in blocks (pixels/8)
    }

static void invade() { // TODO should let the draw to somehting else
  static unsigned long invaderTimerInterval = 500; // between each movement in milisecond
  static unsigned long lastInvaderMoveTime = 0;
  static signed int invasionXmoveCounter = 0; // TODO rename STRAFE_COUNTER
  static uint_fast8_t diveCounter = 0;
  static uint_fast8_t invaderYSpeed = 3;

  if (millis() - lastInvaderMoveTime > invaderTimerInterval) {
    lastInvaderMoveTime = millis();
    bool arrivedOnRight = invaderDirection == 1 && invasionXmoveCounter >= invaderRightXMoveCount;
    bool arrivedOnLeft = invaderDirection == -1 && invasionXmoveCounter <= invaderLeftXMoveCount;
    if (arrivedOnRight  || arrivedOnLeft) { // DIVE
      ++diveCounter;
      //compensateDead();
      invaderDirection = -invaderDirection;
      for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
        if (!invaders[i].isDead) {
          invaders[i].sprite.y += invaderYSpeed;
          drawInvader(&invaders[i],i, invasionXmoveCounter, diveCounter);// TODO wrong neeed another counter for Y
        }
      }
    } else {
      if(invaderDirection == -1) {
        --invasionXmoveCounter;
      } else {
        ++invasionXmoveCounter;
      }     
      for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
        if (!invaders[i].isDead) {
          invaders[i].sprite.x += invaderXSpeed * invaderDirection;
          drawInvader(&invaders[i],i, invasionXmoveCounter, diveCounter);// TODO wrong neeed another counter for Y
        }
      }
    }
  }
}

#endif
