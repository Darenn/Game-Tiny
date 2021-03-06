/**
     Attiny85 PINS
                    ____
     RESET(PB5)   -|_|  |- 3V
     BUTTONS (PB3)-|    |- (PB2) PAD
     SDA (PB4)    -|    |- (PB1) HP
     GND          -|____|- (PB0) SCL
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
#include "ufo.h"
#include"gametiny_font.h"
#include "menus.h"
#define DEBUG

// 0 | 0 | PB5 | PB4 | PB3 | PB2 | PB1 | PB0
#define SETUP_PINS() DDRB |= 0b00010011 // set PB1 as output (for the speaker), PB0 and PB2 as input for buttons, PB4 and PB0 as output for screens

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define TIME_PER_FRAME 32 // in ms

#define PIN_SDA PB4
#define PIN_SCL PB0


void drawIntro() {
  CLEAR_SCREEN();
  delay(500);
  unsigned char gameTinyLogo [160];
  eeprom_read_block(gameTinyLogo, LOGO_EEPROM_ADDR, 160);
  /*for (int8_t y = -24; y < 16; y++)
  {
    ssd1306_drawBuffer(16, y, 40, 32, gameTinyLogo);
    delay(25);
    CLEAR_SCREEN();
  }*/
  ssd1306_drawBuffer(40, 10, 40, 32, gameTinyLogo);
  melody(snd_intro);
  delay(1000);
  CLEAR_SCREEN();
}

void setup() {
  //ssd1306_128x64_i2c_init();
  ssd1306_128x64_i2c_initEx(PIN_SCL,PIN_SDA, 0);
  ssd1306_setFixedFont(TinyFont4x6);

  SETUP_PINS();

  drawIntro();

  drawMainMenu();
  while(!IS_A_BUTTON_PRESSED) {updateInputs();}
  CLEAR_SCREEN();
  initInvaders();
  updateScore(0);
  init_player();
}

void loop() {
  unsigned long startLoopTime = millis();  // Save time to get 30 FPS

  note(0, 0);

  updateInputs();
  playerUpdate();
  invade();
  invadersShoot();
  updateUFO();

  drawShelters();
  playerDraw();

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
