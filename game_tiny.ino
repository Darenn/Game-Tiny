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

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define INVADERS_COUNT 10
#define INVADERS_X_MOVE_COUNT 15

static char tempStr[4] = {0};
void noBufUtoa(uint16_t b)
{
    utoa(b,tempStr,10);
}

Player p;
Invader* invaders [INVADERS_COUNT];

  

void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  pinMode(PIN_BUZZER, OUTPUT);
  ssd1306_clearScreen( );

  for(int i = 0; i < INVADERS_COUNT; i++) {
     invaders[i] = new Invader(INVADER_0, 10 * i, 30);
     invaders[i]->draw();
  }
}

void invade() {
  static unsigned int invaderTimerInterval = 5000; // time between movement in milisecond
  static int invaderTimer = 0;
  static unsigned int lastInvaderMoveTime = 0;
  static char invasionXmoveCounter = 0;
  static char invaderXSpeed = 2;
  static char invaderDirection = 1; // 1 = right and -1 = left
  static char invaderYSpeed = 3;
  
  invaderTimer += millis() - lastInvaderMoveTime;
  if(invaderTimer >= invaderTimerInterval) {
    if(invasionXmoveCounter >= INVADERS_X_MOVE_COUNT) {
      invaderDirection = -invaderDirection;
      invasionXmoveCounter = 0;
      for(int i = 0; i < INVADERS_COUNT; i++) {
          invaders[i]->sprite.y += invaderYSpeed;
          invaders[i]->draw(); 
      }
    } else {
      for(int i = 0; i < INVADERS_COUNT; i++) {
          invaders[i]->sprite.x += invaderXSpeed * invaderDirection;
          invaders[i]->draw(); 
      }
      ++invasionXmoveCounter;
    }
    invaderTimer = 0;
    lastInvaderMoveTime = millis();
  }
}

void loop() {
  note(0, 0);
  float startLoopTime = millis();  // Save time from last loop.
  //ssd1306_clearScreen( );
  char b[10];
  //int keyVal = analogRead(PIN_DPAD);
  //String(keyVal).toCharArray(b,10); 
  //ssd1306_printFixed (0,  8, b, STYLE_NORMAL);
  p.update();
  p.draw();

  invade();
  
  // Fix 30 FPS
  int timeToWait = 32 - (millis() - startLoopTime);
  if(timeToWait > 0) {
    delay(32 - (millis() - startLoopTime));
  }
  String(timeToWait).toCharArray(b,10); 
  ssd1306_printFixed (0,  8, b, STYLE_NORMAL);
}
