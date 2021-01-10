/**
 *   Attiny85 PINS
 *             ____
 *   RESET   -|_|  |- 3V
 *   SCL (3) -|    |- (2)
 *   SDA (4) -|    |- (1) HP
 *   GND     -|____|- (0) INPUT
 *
 *   Atmega328 PINS: connect LCD to A4/A5
 */

#include "ssd1306.h" 
#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "player.h"
#include "invader.h"
#include "debug.h"
#include "physics.h"

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define INVADERS_COUNT 10
#define INVADERS_X_MOVE_COUNT 15 // How many time invaders moves on X axis before going down
#define TIME_PER_FRAME 32 // in ms

Player* p = playerCreate();
Invader* invaders [INVADERS_COUNT];

void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  pinMode(PIN_BUZZER, OUTPUT);
  ssd1306_clearScreen( );

  for(uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
     invaders[i] = new Invader(INVADER_0, 10 * i, 30);
     invaders[i]->draw();
  }
}

static void invade() {
  static unsigned long invaderTimerInterval = 2000; // between each movement in milisecond
  static unsigned long lastInvaderMoveTime = 0;
  static uint_fast8_t invasionXmoveCounter = 0;
  static uint_fast8_t invaderXSpeed = 2;
  static uint_fast8_t invaderDirection = 1; // 1 = right and -1 = left
  static uint_fast8_t invaderYSpeed = 3;

  if(millis() - lastInvaderMoveTime > invaderTimerInterval) {
    lastInvaderMoveTime = millis();
    if(invasionXmoveCounter >= INVADERS_X_MOVE_COUNT) {
      invaderDirection = -invaderDirection;
      invasionXmoveCounter = 0;
      for(uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
          invaders[i]->sprite.y += invaderYSpeed;
          invaders[i]->draw(); 
      }  
    } else {
      ++invasionXmoveCounter;
      for(uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
          invaders[i]->sprite.x += invaderXSpeed * invaderDirection;
          invaders[i]->draw(); 
      }  
    }
  }
}

void loop() {
  note(0, 0);
  float startLoopTime = millis();  // Save time from last loop.
  //ssd1306_clearScreen( );
  char b[10];
  playerUpdate(p);
  playerDraw(p);

  invade();
  
  // Fix 30 FPS
  signed int timeToWait = TIME_PER_FRAME - (millis() - startLoopTime);
  if(timeToWait > 0) {
    delay(TIME_PER_FRAME - (millis() - startLoopTime));
  }
  debugDisplayInt(timeToWait, 0, 0);
  uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  debugDisplayInt(padPinValue, 40, 0);
  debugDisplayInt(digitalRead(PIN_BUTTON_A), 70, 0);

}
