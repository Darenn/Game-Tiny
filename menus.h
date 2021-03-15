#ifndef MENUS_H
#define MENUS_H

#include "utils.h"
#include "graphics.h"
#include "texts.h"

#define PRESS_START_LENGTH 4*5


void drawMainMenu() {

  ssd1306_drawBitmap(24, 0, 80, 24, tinyinvaderstitle);
  
  SPRITE s = ssd1306_createSprite(127/2 - INVADER_WIDTH/2, 24, INVADER_WIDTH, invaderAlienIdle);
  s.draw();
  s = ssd1306_createSprite(127/2 - INVADER_WIDTH/2, 32, INVADER_WIDTH, invaderPoulpeIdle);
  s.draw();
  s = ssd1306_createSprite(127/2 - INVADER_WIDTH/2, 40, INVADER_WIDTH, invaderGhostIdle);
  s.draw();
  s = ssd1306_createSprite((127/4)*3 - INVADER_WIDTH/2, 32, sizeof(ufoBMP), ufoBMP);
  s.draw();

  utoa(SCORE_INVADER_ALIEN, str_buffer, 10);
  ssd1306_printFixed_oldStyle(127/2 + 8, 24, str_buffer, STYLE_NORMAL);

  utoa(SCORE_INVADER_POULPE, str_buffer, 10);
  ssd1306_printFixed_oldStyle(127/2 + 8, 32,str_buffer, STYLE_NORMAL);

  utoa(SCORE_INVADER_GHOST, str_buffer, 10);
  ssd1306_printFixed_oldStyle(127/2 + 8, 40, str_buffer, STYLE_NORMAL);

  utoa(SCORE_UFO_STRONG, str_buffer, 10);
  ssd1306_printFixed_oldStyle((128/4)*3 + 8, 32, str_buffer, STYLE_NORMAL);

  load_text(1);  // Necessary casts and dereferencing, just copy.
  ssd1306_printFixed_oldStyle(127/4 - 24, 32, str_buffer, STYLE_NORMAL);

  while(!eeprom_is_ready()) {}
  uint_fast16_t oldHighScore = eeprom_read_word(HIGH_SCORE_EEPROM_ADDR);

  utoa(oldHighScore, str_buffer, 10); // TODO replace with hightscore
  ssd1306_printFixed_oldStyle(127/4 - 24, 40, str_buffer, STYLE_NORMAL);

  strcpy_P(str_buffer, (char *)pgm_read_word(&(string_table[0])));  // Necessary casts and dereferencing, just copy.
  ssd1306_printFixed_oldStyle(127/2 - PRESS_START_LENGTH/2, 56, str_buffer, STYLE_NORMAL);
}

void drawGameOver(int score, bool isHighScore) {
  CLEAR_SCREEN();
  load_text(TXT_GAME_OVER_ID);
  ssd1306_printFixed_oldStyle(127/2 - 16, 8, str_buffer, STYLE_NORMAL);

  if(isHighScore) {  
    load_text(TXT_NEW_HIGH_SCORE_ID);
    ssd1306_printFixed_oldStyle(127/2 - 16, 32, str_buffer, STYLE_NORMAL);
  } else {
    load_text(TXT_SCORE_ID);
    ssd1306_printFixed_oldStyle(127/2 -  16, 32, str_buffer, STYLE_NORMAL);
  }
  
  utoa(score, str_buffer, 10);
  ssd1306_printFixed_oldStyle(127/2 - 8, 40, str_buffer, STYLE_NORMAL);
}

#endif
