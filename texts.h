#ifndef TEXTS_H
#define TEXTS_H

const char txt_pressStart[] PROGMEM = "EF:DF";
const char txt_highScore[] PROGMEM = "?@>?/E<CD=";
const char txt_score[] PROGMEM = "E<CD=";
const char txt_lives[] PROGMEM = "A@H=E";
const char txt_gameOver[] PROGMEM = ">:B=/CH=D";
const char txt_newHighScore[] PROGMEM = "?@>?/E<CD=";

#define TXT_PRESS_START_ID 0
#define TXT_HIGHSCORE_ID 1
#define TXT_SCORE_ID 2
#define TXT_LIVES_ID 3
#define TXT_GAME_OVER_ID 4
#define TXT_NEW_HIGH_SCORE_ID 5

const char *const string_table[] PROGMEM = {txt_pressStart, txt_highScore, txt_score, txt_lives, txt_gameOver, txt_newHighScore};

char str_buffer[12];  // make sure this is large enough for the largest string it must hold

#define load_text(textID) strcpy_P(str_buffer, (char *)pgm_read_word(&(string_table[textID])))  // Necessary casts and dereferencing, just copy.

#endif
