#ifndef INPUTS_H
#define INPUTS_H

#include "debug.h"

#define PIN_DPAD 7
#define PIN_BUTTONS PB3

#define IS_RIGHT_PAD_PRESSED (padPinValue >= 70) && (padPinValue <= 112) // 71 and 111
#define IS_DOWN_PAD_PRESSED (padPinValue >= 983) && (padPinValue <= 1024) // 984 and 1023
#define IS_LEFT_PAD_PRESSED (padPinValue >= 512) && (padPinValue <= 515) // 513 and 514
#define IS_UP_PAD_PRESSED (padPinValue >= 163) && (padPinValue <= 200) // 164 and 199
#define IS_A_BUTTON_PRESSED (buttonPinValue >= 70) && (buttonPinValue <= 100) // 70 and 100
#define IS_B_BUTTON_PRESSED (buttonPinValue >= 300) && (buttonPinValue <= 600) // random and 512
#define IS_START_BUTTON_PRESSED (buttonPinValue >= 170) && (buttonPinValue <= 190) // random and 184

  //sei();                      // enable all interrupts

uint_fast16_t padPinValue;
uint_fast16_t buttonPinValue;

void updateInputs() {
  padPinValue = analogRead(PIN_DPAD); // analog read is actually very optimized for at tiny
  buttonPinValue = analogRead(PIN_BUTTONS);
}

#endif
