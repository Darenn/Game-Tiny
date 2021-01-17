#ifndef SCORE_H
#define SCORE_H

#define SCORE_INVADER_POULPE 10
#define SCORE_INVADER_ALIEN 20
#define SCORE_INVADER_GHOST 30
#define SCORE_LEVEL_COMPLETED 100
#define SCORE_UFO_WEAK 50
#define SCORE_UFO_STRONG 300


static uint_fast8_t score = 0;

void updateScore(uint_fast8_t toAdd) {
  score += toAdd;
  ssd1306_printFixed_oldStyle(0, 0, "SCORE:", STYLE_NORMAL);
  char tempStr[4] = {0};
  utoa(score, tempStr, 10);
  ssd1306_printFixed_oldStyle(6*6, 0, tempStr, STYLE_NORMAL);
}

#endif
