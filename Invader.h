#ifndef INVADER_H
#define INVADER_H

#include "ssd1306.h"
#include "physics.h"
#include "score.h"


#include "ssd1306.h"

#define INVADER_WIDTH 8 // The width of an invader in pixels
#define INVADER_X_GAP 10 // The gap between each invader on the same row
#define INVADER_Y_GAP 8 // The gap between two rows
#define INVADER_STARTING_Y 8 // The gap between two rows
#define INVADER_STRAFE_SPEED 2 // in pixel per strafe, how much pixels we go on the X axis at each strafe
#define INVADER_DIVE_SPEED 8 // In pixel per dive, how much pixels we go down at each dive
#define INVADERS_COLUMN_COUNT 9 // How much column on the invader matrix (how much invaders on one row)
#define INVADERS_ROW_COUNT 4 // How much rows on the invader matrix
#define INVADERS_COUNT INVADERS_COLUMN_COUNT * INVADERS_ROW_COUNT // Total count of invaders

#define INVADERS_STARTING_STRAFE_TIME 3000
#define INVADERS_STRAFE_TIME_LOSS 100
#define INVADER_STARTING_RIGHT_STRAFE_COUNT_LIMIT 19 // How much time invaders will strafe to the right at start.
#define INVADER_STARTING_LEFT_STRAFE_COUNT_LIMIT 0 // How much time invaders will strafe to the left at start.

#define X_SPEED_RATIO INVADER_WIDTH / INVADER_STRAFE_SPEED // how much strafe move to replace an invader
#define LEFTIEST_ALIVE_COLUMN getColumnWithInvaderIndex(getFirstColumnWithAliveInvader())
#define LEFT_COMPENSATION LEFTIEST_ALIVE_COLUMN * X_SPEED_RATIO
#define RIGHTIEST_ALIVE_COLUMN getColumnWithInvaderIndex(getLastColumnWithAliveInvader())
#define RIGHT_COMPENSATION (INVADERS_COLUMN_COUNT - 1 - RIGHTIEST_ALIVE_COLUMN) * X_SPEED_RATIO

static int_fast8_t invaderDirection = 1; // 1 = right and -1 = left
static int_fast8_t invaderRightStrafeCountLimit = INVADER_STARTING_RIGHT_STRAFE_COUNT_LIMIT; // How many time invaders moves on X axis before going down
static int_fast8_t invaderLeftStrafeCountLimit = 0; // How many time invaders moves on X axis before going down
static int_fast8_t strafeCounter = 0; // How much time we have strafed so far, can be negative if moving on left
static uint_fast8_t diveCounter = 0; // How much time we have dived so far
static int_fast8_t strafeCounterOld = 0; // How much time we have strafed so far, can be negative if moving on left
static uint_fast8_t diveCounterOld = 0; // How much time we have dived so far
static unsigned long strafeInterval = INVADERS_STARTING_STRAFE_TIME; // interval of time between each strafe action in ms

typedef struct Invader {
  bool isDead = false;
} Invader;

Invader invaders [INVADERS_COUNT];

inline static uint_fast8_t getColumnWithInvaderIndex(uint_fast8_t index) {
  return index % INVADERS_COLUMN_COUNT;
}

inline static uint_fast8_t getRowWithInvaderIndex(uint_fast8_t index) {
  return index / INVADERS_COLUMN_COUNT;
}

inline static uint_fast8_t getPosX(uint_fast8_t idx, uint_fast8_t strafeCounter = strafeCounter) {
#define ld_posXStart getColumnWithInvaderIndex(idx) * INVADER_X_GAP
#define ld_offsetXStrafe strafeCounter * INVADER_STRAFE_SPEED
  return ld_posXStart + ld_offsetXStrafe;
}

inline static uint_fast8_t getPosY(uint_fast8_t idx,uint_fast8_t diveCounter = diveCounter) {
  return INVADER_STARTING_Y + getRowWithInvaderIndex(idx) * INVADER_Y_GAP + diveCounter * INVADER_DIVE_SPEED;
}

void killInvader(Invader *invader, uint_fast8_t i) {
  strafeInterval -= INVADERS_STRAFE_TIME_LOSS;
  invader->isDead = true;
  if(i>7) {
    updateScore(10);
  } else if(i > 15) {
    updateScore(20);
  } else {
    updateScore(30);
  }
  ssd1306_clearBlock(getPosX(i), getPosY(i), INVADER_WIDTH, INVADER_WIDTH);
}

inline static uint_fast8_t getIndexByCoordinates(uint_fast8_t row, uint_fast8_t col) {
  return col + row * INVADERS_COLUMN_COUNT;
}

/*
 * Returns the first column (leftiest) with an invader still alive.
 * TODO can I optimize ny removing the return statement?
 */
uint_fast8_t getFirstColumnWithAliveInvader() {
  for (uint_fast8_t col = 0; col < INVADERS_COLUMN_COUNT; ++col) {
    for (uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if (!invaders[getIndexByCoordinates(row, col)].isDead) {
        return col;
      }
    }
  }
  return 99;
}

/*
 * Returns the last column (rightiest) with an invader still alive.
 */
uint_fast8_t getLastColumnWithAliveInvader() {
  for (uint_fast8_t col = INVADERS_COLUMN_COUNT - 1; col > 0; --col) {
    for (uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if (!invaders[getIndexByCoordinates(row, col)].isDead) {
        return col;
      }
    }
  }
  return 99;
}

/*
   Find the most to the right alien alive to calculate how much more we should move to the right (in strafe move) (and same with the left).
   Then change both X move limits for right and left.
*/
inline static void compensateDead() {
  invaderRightStrafeCountLimit = INVADER_STARTING_RIGHT_STRAFE_COUNT_LIMIT + RIGHT_COMPENSATION;
  invaderLeftStrafeCountLimit = INVADER_STARTING_LEFT_STRAFE_COUNT_LIMIT - LEFT_COMPENSATION;
}

void drawInvader(Invader* i, uint_fast8_t index, uint_fast8_t strafeCounter, uint_fast8_t diveCounter) {
  SPRITE s = ssd1306_createSprite(getPosX(index, strafeCounter), getPosY(index, diveCounter), sizeof(invaderAlienIdle), invaderAlienIdle);
  if(index>7) {
    s = ssd1306_createSprite(getPosX(index, strafeCounter), getPosY(index, diveCounter), sizeof(invaderPoulpeIdle), invaderPoulpeIdle);
    /*if(strafeCounter % 2 != 0) {
      ssd1306_createSprite(getPosX(index, strafeCounter), getPosY(index, diveCounter), sizeof(invaderPoulpeMove), invaderPoulpeMove);
    } else {
      s = ssd1306_createSprite(getPosX(index, strafeCounter), getPosY(index, diveCounter), sizeof(invaderPoulpeIdle), invaderPoulpeIdle);
    }*/
      
  } else if(index > 15) {
    s = ssd1306_createSprite(getPosX(index, strafeCounter), getPosY(index, diveCounter), sizeof(invaderGhostIdle), invaderGhostIdle);
  }

  ssd1306_drawSprite(&s);
}

/*
   Should be called only when they move to avoid flickering.
*/
static inline drawInvaders() {
  int posX = getPosX(0, strafeCounterOld);
  int posY = getPosY(0, diveCounterOld);
  int posX1 = posX + (INVADERS_COLUMN_COUNT)*INVADER_X_GAP;
  int posY2 = posY + (INVADERS_ROW_COUNT)*INVADER_Y_GAP;
  clearRect(posX, posY, posX1, posY2);
  for (int_fast8_t i = INVADERS_COUNT-1; i >= 0; i--) {
    if (!invaders[i].isDead) {
      drawInvader(&invaders[i], i, strafeCounter, diveCounter);
    }
  }
}

static void invade() {
  static unsigned long lastStrafeTime = 0;  // the last time we strafed in ms
  static uint_fast8_t diveSpeed = 3; // How much pixel should go down when diving

  if (millis() - lastStrafeTime > strafeInterval) {
    lastStrafeTime = millis();
#define ld_arrivedOnRight invaderDirection == 1 && strafeCounter >= invaderRightStrafeCountLimit
#define ld_arrivedOnLeft invaderDirection == -1 && strafeCounter <= invaderLeftStrafeCountLimit
    if (ld_arrivedOnRight || ld_arrivedOnLeft) { // DIVE
      diveCounterOld = diveCounter;
      ++diveCounter;
      invaderDirection = -invaderDirection;
    } else {
      strafeCounterOld = strafeCounter;
      if (invaderDirection == -1) {    
        --strafeCounter;
      } else {
        ++strafeCounter;
      }
    }
    drawInvaders(); // draw the invaders only when they move
  }
}

Rect getInvaderRect(int_fast8_t x, int_fast8_t y) {
  return Rect{x, y, x + INVADER_WIDTH, y + INVADER_WIDTH};
}


#endif
