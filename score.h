#ifndef SCORE_H
#define SCORE_H

#define SCORE_INVADER_POULPE 10
#define SCORE_INVADER_ALIEN 20
#define SCORE_INVADER_GHOST 30
#define SCORE_LEVEL_COMPLETED 100
#define SCORE_UFO_WEAK 50
#define SCORE_UFO_STRONG 300

void updateScore(uint_fast8_t toAdd) {
  static uint_fast16_t score = 0;
  score += toAdd;
  ssd1306_printFixed_oldStyle(0, 0, "SCORE:", STYLE_NORMAL);
  //char tempStr[6] = {0};
  //utoa(tempStr, score, 10);
  //ssd1306_printFixed_oldStyle(40, 0, tempStr, STYLE_NORMAL);
  debugDisplayInt(freeMemory(), 0, 50);
  delay(1000);
}

#endif
