#ifndef INPUTS_H
#define INPUTS_H

#include "debug.h"

#define PIN_DPAD 7
#define PIN_BUTTON_A PB0

#define IS_RIGHT_PAD_PRESSED padPinValue >= 660 && padPinValue <= 760
#define IS_DOWN_PAD_PRESSED padPinValue >= 460 && padPinValue <= 560
#define IS_LEFT_PAD_PRESSED padPinValue >= 2 && padPinValue <= 30
#define IS_UP_PAD_PRESSED padPinValue >= 850 && padPinValue <= 1020
#define IS_A_BUTTON_PRESSED buttonPinValue == 1
#define IS_B_BUTTON_PRESSED padPinValue >= 1021 && padPinValue <= 1030

  //sei();                      // enable all interrupts

static uint_fast16_t padPinValue;
static uint_fast16_t buttonPinValue;

void updateInputs() {
  padPinValue = analogRead(PIN_DPAD); // analog read is actually very optimized for at tiny
  buttonPinValue = PINB & 0b00000001; // read form pb0
}

#endif
