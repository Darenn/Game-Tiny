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

#define DEBUG

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define TIME_PER_FRAME 32 // in ms



Player* p = playerCreate();
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
      drawInvader(&invaders[x + y * INVADERS_COUNT_PER_ROW], x + y * INVADERS_COUNT_PER_ROW , 0, 0);
    }
  }

  theBullet.sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);
  theBullet.enabled = false;

  playerForceDraw(p);
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

        compensateDead(false);
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
  signed int timeToWait = (signed int)TIME_PER_FRAME - (millis() - startLoopTime);
  if (timeToWait >= 0 && timeToWait < 33) {
    delay(timeToWait);
  } else {
    //delay (3000);
  }

  // DEBUG
  //debugDisplayInt(invaderXMoveCount, 0, 50);

  //debugDisplayInt(freeMemory(), 0, 50);
  //debugDisplayInt(timeToWait, 55, 120);
  //uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  //debugDisplayInt(padPinValue, 40, 0);
  //debugDisplayInt(digitalRead(PIN_BUTTON_A), 70, 0);
}
