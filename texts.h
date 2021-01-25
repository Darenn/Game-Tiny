#ifndef TEXTS_H
#define TEXTS_H

const char txt_pressStart[] PROGMEM = "A@H=E";
const char txt_highScore[] PROGMEM = "A@H=E";
const char txt_score[] PROGMEM = "E<CD=";
const char txt_lives[] PROGMEM = "A@H=E";

#define TXT_PRESS_START_ID 0
#define TXT_HIGHSCORE_ID 1
#define TXT_SCORE_ID 2
#define TXT_LIVES_ID 3

const char *const string_table[] PROGMEM = {txt_pressStart, txt_highScore, txt_score, txt_lives};

char str_buffer[30];  // make sure this is large enough for the largest string it must hold

#define load_text(textID) strcpy_P(str_buffer, (char *)pgm_read_word(&(string_table[textID])))  // Necessary casts and dereferencing, just copy.

#endif
