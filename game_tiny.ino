
/**
     Attiny85 PINS
                    ____
     RESET(PB5)   -|_|  |- 3V
     SCL (PB3)    -|    |- (PB2) PAD
     SDA (PB4)    -|    |- (PB1) HP
     GND          -|____|- (PB0) A
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
#include "score.h"

#define DEBUG

// 0 | 0 | PB5 | PB4 | PB3 | PB2 | PB1 | PB0
#define SETUP_PINS DDRB |= 0b00011010 // set PB1 as output (for the speaker), PB0 and PB2 as input for buttons, PB4 and PB3 as output for screens

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define TIME_PER_FRAME 32 // in ms

Player p;
//Bullet theBullet;

inline void drawIntro() {
  clearRect(0, 0, 127, 63); // clear screen
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
  clearRect(0, 0, 127, 63); // clear screen
}

void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  
  SETUP_PINS;

  drawIntro();
  initInvaders();

  /*theBullet.sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);
  theBullet.enabled = false;*/
  updateScore(0);

  init_player(&p);
}

void loop() {
  float startLoopTime = millis();  // Save time to get 30 FPS
  
  note(0, 0);
  updateInputs();
  playerUpdate(&p);
  //bulletUpdate(&theBullet);

  invade();
  invadersShoot();

  if (IS_A_BUTTON_PRESSED) {
    
  }

  playerDraw(&p);
  
  // Fix 30 FPS
  signed int timeToWait = (signed int)TIME_PER_FRAME - (millis() - startLoopTime);
  if (timeToWait >= 0 && timeToWait < 33) {
    //debugDisplayInt(timeToWait, 50, 0);
    delay(timeToWait);
  } else {
    //delay (3000);
  }

  //drawInvaders();
  // DEBUG
  //debugDisplayInt(PINB & 0b00000001, 0, 50);
  //debugDisplayInt(sizeof(Invader), 0, 50);
  //debugDisplayInt(freeMemory(), 0, 50);
  
  //uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  //debugDisplayInt(padPinValue, 40, 0);
  //debugDisplayInt(digitalRead(PIN_BUTTON_A), 70, 0);
}
