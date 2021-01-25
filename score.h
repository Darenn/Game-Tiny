#ifndef SCORE_H
#define SCORE_H

#define SCORE_INVADER_POULPE 10
#define SCORE_INVADER_ALIEN 20
#define SCORE_INVADER_GHOST 30
#define SCORE_LEVEL_COMPLETED 100
#define SCORE_UFO_WEAK 50
#define SCORE_UFO_STRONG 300

#include "texts.h";



void updateScore(uint_fast16_t toAdd) {
  static uint_fast16_t score = 0;
  score += toAdd;
  load_text(TXT_SCORE_ID);
  ssd1306_printFixed_oldStyle(0, 0, str_buffer, STYLE_NORMAL);
  utoa(score, str_buffer, 10);
  ssd1306_printFixed_oldStyle(4*6, 0, str_buffer, STYLE_NORMAL);
}

#endif
