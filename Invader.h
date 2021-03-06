#ifndef INVADER_H
#define INVADER_H

#include "ssd1306.h"
#include "physics.h"
#include "score.h"
#include "bullet.h"
#include "utils.h"

#include "ssd1306.h"

#define INVADER_WIDTH 8 // The width of an invader in pixels
#define INVADER_X_GAP 10 // The gap between each invader on the same row
#define INVADER_Y_GAP 8 // The gap between two rows
#define INVADER_STARTING_Y 8 // The gap between two rows
#define INVADER_STRAFE_SPEED 2 // in pixel per strafe, how much pixels we go on the X axis at each strafe
#define INVADER_DIVE_SPEED 8 // In pixel per dive, how much pixels we go down at each dive
#define INVADERS_COLUMN_COUNT 9 // How much column on the invader matrix (how much invaders on one row)
#define INVADERS_ROW_COUNT 3 // How much rows on the invader matrix
#define INVADERS_COUNT INVADERS_COLUMN_COUNT * INVADERS_ROW_COUNT // Total count of invaders

#define INVADERS_STARTING_STRAFE_TIME 1800 //3000
#define INVADERS_STRAFE_TIME_LOSS_WAVE 200
#define INVADERS_STRAFE_TIME_LOSS 40
#define INVADER_STARTING_RIGHT_STRAFE_COUNT_LIMIT 19 // How much time invaders will strafe to the right at start.
#define INVADER_STARTING_LEFT_STRAFE_COUNT_LIMIT 0 // How much time invaders will strafe to the left at start.

#define X_SPEED_RATIO INVADER_WIDTH / INVADER_STRAFE_SPEED // how much strafe move to replace an invader
#define LEFTIEST_ALIVE_COLUMN getColumnWithInvaderIndex(getFirstColumnWithAliveInvader())
#define LEFT_COMPENSATION LEFTIEST_ALIVE_COLUMN * X_SPEED_RATIO
#define RIGHTIEST_ALIVE_COLUMN getColumnWithInvaderIndex(getLastColumnWithAliveInvader())
#define RIGHT_COMPENSATION (INVADERS_COLUMN_COUNT - 1 - RIGHTIEST_ALIVE_COLUMN) * X_SPEED_RATIO

#define STARTING_TIME_BETWEEN_SHOTS_MIN 30 * 1 // in frame
#define STARTING_TIME_BETWEEN_SHOTS_MAX 30 * 3 // in frame
#define TIME_LOSS_BETWEEN_SHOTS 10

/*
   Find the most to the right alien alive to calculate how much more we should move to the right (in strafe move) (and same with the left).
   Then change both X move limits for right and left.
*/
#define INVADER_RIGHT_STRAFE_COUNT_LIMIT INVADER_STARTING_RIGHT_STRAFE_COUNT_LIMIT + RIGHT_COMPENSATION // How many time invaders moves on X axis before going down
#define INVADER_LEFT_STRAFE_COUNT_LIMIT INVADER_STARTING_LEFT_STRAFE_COUNT_LIMIT - LEFT_COMPENSATION // How many time invaders moves on X axis before going down


#define getIndexByCoordinates(row, col) col + row * INVADERS_COLUMN_COUNT

static int_fast8_t strafeCounter = 0; // How much time we have strafed so far, can be negative if moving on left
static uint_fast8_t deadInvaders;
uint_fast8_t invadersStates [INVADERS_COUNT / 8 + 1];

static Bullet bulletFast;
uint_fast8_t strafeCounterOld;
uint_fast8_t diveCounterOld;
static uint_fast16_t invaders_strafe_time = INVADERS_STARTING_STRAFE_TIME;

static uint_fast16_t max_time_between_shots = STARTING_TIME_BETWEEN_SHOTS_MAX;

static struct InvaderBrain {
  uint_fast8_t noteCounter: 3; // max7
  bool invaderDirection: 1; // false = right; true = left
  uint_fast8_t diveCounter: 4; //max 15  // How much time we have dived so far
} invaderBrain {.noteCounter = 4, .invaderDirection = false};

bool isDead(uint_fast8_t i) {
  return CHECK_BIT(invadersStates[i/8], i % 8);
}

void setDead(uint_fast8_t i) {
  SET_BIT(invadersStates[i/8], i % 8);
}

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

inline static uint_fast8_t getPosY(uint_fast8_t idx, uint_fast8_t diveCounter = invaderBrain.diveCounter) {
  return INVADER_STARTING_Y + getRowWithInvaderIndex(idx) * INVADER_Y_GAP + diveCounter * INVADER_DIVE_SPEED;
}

typedef void ( *fn_t )( void );

void newWave() {
  melody(snd_newWave);
  strafeCounter = 0;
  deadInvaders = 0;
  strafeCounterOld = 0;
  diveCounterOld = 0;
  invaderBrain.noteCounter = 4;
  invaderBrain.invaderDirection = false;
  invaderBrain.diveCounter = 0;
  invaders_strafe_time -= INVADERS_STRAFE_TIME_LOSS_WAVE;
  max_time_between_shots -= TIME_LOSS_BETWEEN_SHOTS;
  if(max_time_between_shots < STARTING_TIME_BETWEEN_SHOTS_MIN) {
    max_time_between_shots = STARTING_TIME_BETWEEN_SHOTS_MIN;
  }
  size_t i;
  for(i = 0; i < INVADERS_COUNT; ++i)
  {
    CLEAR_BIT(invadersStates[i/8], i % 8);
  }
}

static void killInvader(uint_fast8_t i) {
  setDead(i);
  note(1,1);
  uint8_t score = 30;
  if (i >= INVADERS_COLUMN_COUNT) {
    score = 10;
  } else if (i >= INVADERS_COLUMN_COUNT * 2) {
    score = 20;
  } 
  updateScore(score);
  if (++deadInvaders >= INVADERS_COUNT) {
    // TODO call win screen
    // for now just reset
    // TODO note(0,0);
    newWave();
    /*do
      {
      wdt_enable(WDTO_15MS);
      for (;;)
      {
      }
      } while (0);*/
  }
}

/*
   Returns the first column (leftiest) with an invader still alive.
   TODO can I optimize ny removing the return statement?
*/
static uint_fast8_t getFirstColumnWithAliveInvader() {
  for (uint_fast8_t col = 0; col < INVADERS_COLUMN_COUNT; ++col) {
    for (uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if (!isDead(getIndexByCoordinates(row, col))) {
        return col;
      }
    }
  }
  return 0;
}

/*
   Returns the last row with an invader still alive.
*/
static uint_fast8_t getLastRowWithAliveInvader() {
  for (int_fast8_t i = INVADERS_COUNT - 1; i > 0; --i) {
    if (!isDead(i)) {
      return i % INVADERS_COLUMN_COUNT;
    }
  }
  return 0;
}


/*
   Returns the last column (rightiest) with an invader still alive.
*/
static uint_fast8_t getLastColumnWithAliveInvader() {
  for (int_fast8_t col = INVADERS_COLUMN_COUNT - 1; col > 0; --col) {
    for (uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if (!isDead(getIndexByCoordinates(row, col))) {
        return col;
      }
    }
  }
  return 0;
}


void drawInvader(uint_fast8_t index, uint_fast8_t strafeCounter, uint_fast8_t diveCounter) {
  const uint8_t *spriteToDisplay;
  if (index >= INVADERS_COLUMN_COUNT * 2) {
    if (strafeCounter & 1) {
      spriteToDisplay = invaderGhostMove;
    } else {
      spriteToDisplay = invaderGhostIdle;
    }
  }
  else if (index >= INVADERS_COLUMN_COUNT) {
    if (strafeCounter & 1) {
      spriteToDisplay = invaderPoulpeMove;
    } else {
      spriteToDisplay = invaderPoulpeIdle;
    }
  } else {
    if (strafeCounter & 1) {
      spriteToDisplay = invaderAlienMove;
    } else {
      spriteToDisplay = invaderAlienIdle;
    }
  }
  SPRITE s = ssd1306_createSprite(getPosX(index, strafeCounterOld), getPosY(index, diveCounterOld), INVADER_WIDTH, spriteToDisplay);
  //s.erase();
  s.x = getPosX(index, strafeCounter);
  s.y = getPosY(index, diveCounter); 
  s.draw();
}

/*
   Should be called only when they move to avoid flickering.
*/
static inline void drawInvaders() {
  int posX = getPosX(0, strafeCounterOld);
  int posY = getPosY(0, diveCounterOld);
  int posX1 = posX + INVADERS_COLUMN_COUNT*INVADER_X_GAP;
  int posY2 = posY + INVADERS_ROW_COUNT*INVADER_Y_GAP;
  clearRect(posX,posY, posX1, posY2);
  for (int_fast8_t i = INVADERS_COUNT - 1; i >= 0; i--) {
    if (!isDead(i)) {
      drawInvader(i, strafeCounter, invaderBrain.diveCounter);
    }
  }
}



static void invade() {
  static unsigned long lastStrafeTime = 0;  // the last time we strafed in ms
  signed long timeToWait = 20;
  if (invaders_strafe_time - deadInvaders * INVADERS_STRAFE_TIME_LOSS >= 0 && invaders_strafe_time - deadInvaders * INVADERS_STRAFE_TIME_LOSS < 10000) {
    timeToWait = invaders_strafe_time - deadInvaders * INVADERS_STRAFE_TIME_LOSS;
  }
  if (millis() - lastStrafeTime > invaders_strafe_time - deadInvaders * INVADERS_STRAFE_TIME_LOSS) {
    if (invaderBrain.noteCounter <= 0) invaderBrain.noteCounter = 4;
    note(--invaderBrain.noteCounter, 3);
    lastStrafeTime = millis();
#define ld_arrivedOnRight (!invaderBrain.invaderDirection) && (strafeCounter >= INVADER_RIGHT_STRAFE_COUNT_LIMIT)
#define ld_arrivedOnLeft (invaderBrain.invaderDirection) && (strafeCounter <= INVADER_LEFT_STRAFE_COUNT_LIMIT)
    if (ld_arrivedOnRight || ld_arrivedOnLeft) { // DIVE
      diveCounterOld = invaderBrain.diveCounter;
      ++invaderBrain.diveCounter;
      invaderBrain.invaderDirection = !invaderBrain.invaderDirection;
    } else {
      strafeCounterOld = strafeCounter;
      if (invaderBrain.invaderDirection) {
        --strafeCounter;
      } else {
        ++strafeCounter;
      }
    }
    drawInvaders(); // draw the invaders only when they move
  }
}

/*
   Returns the lowest alive alien on given column
*/
uint_fast8_t getLastRowWithAliveInvaderOnColumn(uint_fast8_t col) {
  for (int_fast8_t row = INVADERS_ROW_COUNT - 1; row > 0; --row) {
    if (!isDead(getIndexByCoordinates(row, col))) {
      return row;
    }
  }
  return 0;
}

static void invadersShoot() {
  static uint_fast8_t timeUntilNextShot = GT_RANDOM_RANGE(STARTING_TIME_BETWEEN_SHOTS_MIN, max_time_between_shots);
  static uint_fast8_t shotTimer = 0;

  ++shotTimer;
  if (shotTimer >= timeUntilNextShot) {
    shotTimer = 0;
    timeUntilNextShot = GT_RANDOM_RANGE(STARTING_TIME_BETWEEN_SHOTS_MIN, max_time_between_shots);
    const uint_fast8_t col = GT_RANDOM_RANGE(getFirstColumnWithAliveInvader(), getLastColumnWithAliveInvader());
    const uint_fast8_t row = getLastRowWithAliveInvaderOnColumn(col);
    const uint_fast8_t index = getIndexByCoordinates(row, col);
    shoot(&bulletFast, getPosX(index) + INVADER_WIDTH / 2, getPosY(index) + INVADER_WIDTH); // TODO IT USEs THE PLAYER SPRITE
  }
  updateFastBullet(&bulletFast);
}

/* does not benefit from this opti
  #define getInvaderRect(x, y) Rect{x, y, x + INVADER_WIDTH, y + INVADER_WIDTH}
*/
Rect getInvaderRect(int_fast8_t x, int_fast8_t y) {
  return Rect{x, y, x + INVADER_WIDTH, y + INVADER_WIDTH};
}

void initInvaders() {
  for (uint_fast8_t y = 0; y < INVADERS_ROW_COUNT; ++y) {
    for (uint_fast8_t x = 0; x < INVADERS_COLUMN_COUNT; ++x) {
      //invaders[x + y * INVADERS_COLUMN_COUNT] = Invader();
      drawInvader(x + y * INVADERS_COLUMN_COUNT , 0, 0);
    }
  }
  bulletFast.sprite = ssd1306_createSprite(0, 0, sizeof(bulletFast1), bulletFast1);
  bulletFast.directionnalSpeed = FAST_BULLET_SPEED;
}


#endif
