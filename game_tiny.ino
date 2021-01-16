/**
     Attiny85 PINS
                    ____
     RESET(PB5)   -|_|  |- 3V
     SCL (PB3)    -|    |- (PB2)
     SDA (PB4)    -|    |- (PB1) HP
     GND          -|____|- (PB0) INPUT
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

  delay(500);

  for (int8_t y=-24; y<16; y++)
  {
        gfx_drawMonoBitmap(16, y, 40, 32, gameTinyLogo);
        delay(25);
  }
  ssd1306_printFixed_oldStyle(60, 29, "SPACE", STYLE_NORMAL);
  ssd1306_printFixed_oldStyle(65, 32, "INVADERS", STYLE_NORMAL);
  beep(200,600);
  beep(300,200);
  beep(400,300);
  
  delay(2000);

  ssd1306_clearScreen( );

  for (uint_fast8_t y = 0; y < INVADERS_ROW_COUNT; ++y) {
    for (uint_fast8_t x = 0; x < INVADERS_COLUMN_COUNT; ++x) {
      invaders[x + y * INVADERS_COLUMN_COUNT] = Invader();
      drawInvader(&invaders[x + y * INVADERS_COLUMN_COUNT], x + y * INVADERS_COLUMN_COUNT , 0, 0);
    }
  }

  theBullet.sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);
  theBullet.enabled = false;

  playerForceDraw(p);
}

void loop() {
  float startLoopTime = millis();  // Save time to get 30 FPS
  //ssd1306_clearScreen();

  //ssd1306_setColor(RGB_COLOR8(0, 0, 0));
  //ssd1306_fillRect(0, 0, 128, 64);
  
  note(0, 0);
  

  playerUpdate(p);

  if (theBullet.enabled) {
    for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
      uint_fast8_t x = getPosX(i);
      uint_fast8_t y = getPosY(i);   
      if (!invaders[i].isDead && isColliding(getBulletRect(&theBullet), getInvaderRect(x, y))) {
        kill(&theBullet);
        killInvader(&invaders[i], i);
        compensateDead();
        drawInvaders();
        break;
      }
    }
    if (theBullet.enabled) {
      bulletUpdate(&theBullet);
      bulletDraw(&theBullet);
    }
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
    debugDisplayInt(timeToWait, 50, 0);
    delay(timeToWait);
  } else {
    //delay (3000);
  }

  //drawInvaders();
  // DEBUG
  //debugDisplayInt(invaderXMoveCount, 0, 50);
  //debugDisplayInt(sizeof(Invader), 0, 50);
  //debugDisplayInt(freeMemory(), 0, 50);
  
  //uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  //debugDisplayInt(padPinValue, 40, 0);
  //debugDisplayInt(digitalRead(PIN_BUTTON_A), 70, 0);
}
