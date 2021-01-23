#ifndef INPUTS_H
#define INPUTS_H

#include "debug.h"

#define PIN_DPAD 7
#define PIN_BUTTON_A PB0

#define IS_RIGHT_PAD_PRESSED (pinInputs.padPinValue >= 660) && (pinInputs.padPinValue <= 760)
#define IS_DOWN_PAD_PRESSED (pinInputs.padPinValue >= 460) && (pinInputs.padPinValue <= 560)
#define IS_LEFT_PAD_PRESSED (pinInputs.padPinValue >= 2) && (pinInputs.padPinValue <= 30)
#define IS_UP_PAD_PRESSED (pinInputs.padPinValue >= 850) && (pinInputs.padPinValue <= 1020)
#define IS_A_BUTTON_PRESSED pinInputs.buttonPinValue == 1
#define IS_B_BUTTON_PRESSED (pinInputs.padPinValue >= 1021) && (pinInputs.padPinValue <= 1030)

  //sei();                      // enable all interrupts

static struct PinInputs {
  uint_fast16_t padPinValue:15;
  bool buttonPinValue:1;
} pinInputs;


void updateInputs() {
  pinInputs.padPinValue = analogRead(PIN_DPAD); // analog read is actually very optimized for at tiny
  pinInputs.buttonPinValue = PINB & 0b00000001; // read form pb0
}

#endif
