/**
     Attiny85 PINS
               ____
     RESET   -|_|  |- 3V
     SCL (3) -|    |- (2)
     SDA (4) -|    |- (1) HP
     GND     -|____|- (0) INPUT

     Atmega328 PINS: connect LCD to A4/A5
*/

#include "ssd1306.h"
#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "player.h"
#include "invader.h"
#include "debug.h"
#include "physics.h"
#include "bullet.h"



#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define INVADERS_COUNT_PER_ROW 10 // TODO rename column
#define INVADERS_ROW_COUNT 2
#define INVADERS_COUNT INVADERS_COUNT_PER_ROW * INVADERS_ROW_COUNT
#define TIME_PER_FRAME 32 // in ms
#define INVADER_WIDTH 8
#define STARTING_INVADER_X_MOVE_COUNT 15

int invaderXMoveCount = STARTING_INVADER_X_MOVE_COUNT; // How many time invaders moves on X axis before going down

Player* p = playerCreate();
Invader invaders [INVADERS_COUNT];
Bullet theBullet;

void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  //pinMode(PIN_BUZZER, OUTPUT);
  //setup_inputs();
  DDRB |= 0b00011010;         // set PB1 as output (for the speaker), PB0 and PB2 as input
  //sei();                      // enable all interrupts*/ //TODO more optimized than pinmode?

  ssd1306_clearScreen( );

  for (uint_fast8_t y = 0; y < INVADERS_ROW_COUNT; ++y) {
    for (uint_fast8_t x = 0; x < INVADERS_COUNT_PER_ROW; ++x) {
      invaders[x + y * INVADERS_COUNT_PER_ROW] = Invader(INVADER_0, 10 * x, 10 * y);
      invaders[x + y * INVADERS_COUNT_PER_ROW].draw();
    }
  }

  theBullet.sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);
  theBullet.enabled = false;

  playerForceDraw(p);
}

uint_fast8_t invaderCounter = 0; // On each invade call we move only one row for performance
static signed int invaderDirection = 1; // 1 = right and -1 = left
static uint_fast8_t nextInvaderXMoveCount = invaderXMoveCount;
static uint_fast8_t invaderXSpeed = 2; // TODO wont change should be define

static void invade() {
  static unsigned long invaderTimerInterval = 100; // between each movement in milisecond
  static unsigned long lastInvaderMoveTime = 0;
  static uint_fast8_t invasionXmoveCounter = 0;
  
  
  static uint_fast8_t invaderYSpeed = 3;

  if (millis() - lastInvaderMoveTime > invaderTimerInterval) {
    lastInvaderMoveTime = millis();
    if (invasionXmoveCounter >= invaderXMoveCount) {
      invaderDirection = -invaderDirection;
      invasionXmoveCounter = 0;
      invaderXMoveCount = nextInvaderXMoveCount;
      for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
        if (!invaders[i].isDead) {
          invaders[i].sprite.y += invaderYSpeed;
          invaders[i].draw();
        }
      }
    } else {
      ++invasionXmoveCounter;
      for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
        if (!invaders[i].isDead) {
          invaders[i].sprite.x += invaderXSpeed * invaderDirection;
          invaders[i].draw();
        }
      }
    }
  }
}


int getColumnWithInvaderIndex(int index) {
  return index % INVADERS_COUNT_PER_ROW;
}

int getIndexByCoordinates(int row, int col) {
  return col + row*INVADERS_COUNT_PER_ROW;
}

uint_fast8_t getFirstInvaderAliveCol() {
  for(uint_fast8_t col = 0; col < INVADERS_COUNT_PER_ROW; ++col) {
    for(uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if(!invaders[getIndexByCoordinates(row, col)].isDead) {
        return col;
      }
    }
  }
  return 99;
}

uint_fast8_t getLastInvaderAliveCol() {
  for(uint_fast8_t col = INVADERS_COUNT_PER_ROW-1; col > 0; --col) {
    for(uint_fast8_t row = 0; row < INVADERS_ROW_COUNT; ++row) {
      if(!invaders[getIndexByCoordinates(row, col)].isDead) {
        return col;
      }
    }
  }
  return 99;
}

// TODO should compensate when killing an invader to be able to go father before dive
void compensateDead() {
  uint_fast8_t leftiestAliveColumn = getColumnWithInvaderIndex(getFirstInvaderAliveCol());
  uint_fast8_t leftCompensation = leftiestAliveColumn*(INVADER_WIDTH/invaderXSpeed);
  uint_fast8_t rightiestAliveColumn = getColumnWithInvaderIndex(getLastInvaderAliveCol());
  uint_fast8_t rightCompensation = (INVADERS_COUNT_PER_ROW-1-rightiestAliveColumn)*(INVADER_WIDTH/invaderXSpeed);

  static uint_fast8_t oldRightCompensation = 0;
  static uint_fast8_t oldLeftCompensation = 0;

  debugDisplayInt(leftCompensation, 40, 50);
  debugDisplayInt(rightCompensation, 80, 50);
  

  // If we are moving in the direction, apply the new compensation
  if(invaderDirection > 0) { // moving to right
    invaderXMoveCount = STARTING_INVADER_X_MOVE_COUNT + rightCompensation - oldRightCompensation + oldLeftCompensation;
    nextInvaderXMoveCount = invaderXMoveCount + leftCompensation - oldLeftCompensation;
    
  } else { // moving to left invaderDirection < 0
    invaderXMoveCount = STARTING_INVADER_X_MOVE_COUNT + leftCompensation - oldLeftCompensation + oldRightCompensation;
    nextInvaderXMoveCount = invaderXMoveCount + rightCompensation - oldRightCompensation;
  }

  delay(2000);

 // nextInvaderXMoveCount = STARTING_INVADER_X_MOVE_COUNT + leftCompensation + rightCompensation; // adding the other compensation at next dive

  oldRightCompensation = rightCompensation;
  oldLeftCompensation = leftCompensation;
}
  



void loop() {
  float startLoopTime = millis();  // Save time to get 30 FPS
  note(0, 0);

  playerUpdate(p);
  
  if (theBullet.enabled) {
    for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
      if (!invaders[i].isDead && isColliding(&theBullet.sprite, &invaders[i].sprite)) {
        kill(&theBullet);
        invaders[i].kill();

        compensateDead();
        break;
      }
    }
    bulletUpdate(&theBullet);
    bulletDraw(&theBullet);
  }

  invade();

  if (getButtonAPressed()) {
    theBullet.enabled = true;
    theBullet.sprite.x = p->sprite.x + 3;
    theBullet.sprite.y = p->sprite.y - 5;
  }

  playerDraw(p);

  // Fix 30 FPS
  signed int timeToWait = TIME_PER_FRAME - (millis() - startLoopTime);
  if (timeToWait > 0) {
    delay(timeToWait);
  }

  // DEBUG
  debugDisplayInt(invaderXMoveCount, 0, 50);
  //debugDisplayInt(freeMemory(), 0, 50);
  //debugDisplayInt(timeToWait, 0, 0);
  //uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  //debugDisplayInt(padPinValue, 40, 0);
  //debugDisplayInt(digitalRead(PIN_BUTTON_A), 70, 0);
}
