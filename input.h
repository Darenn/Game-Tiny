#ifndef INPUTS_H
#define INPUTS_H

#include "debug.h"

#define PIN_DPAD 7
#define PIN_BUTTON_A PB0

void setup_inputs() {
  pinMode(PIN_DPAD, INPUT);
  pinMode(PIN_BUTTON_A, INPUT);
}

bool getPadRightPressed() {
  uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  return padPinValue >= 660 && padPinValue <= 760; 
}

bool getPadDownPressed() {
  uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  return padPinValue >= 460 && padPinValue <= 560; 
}

bool getPadLeftPressed() {
  uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  return padPinValue >= 2 && padPinValue <= 30; 
}

bool getPadUpPressed() {
  uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  return padPinValue >= 850 && padPinValue <= 1020; 
}

bool getButtonBPressed() {
  uint_fast16_t padPinValue = analogRead(PIN_DPAD);
  return padPinValue >= 1021 && padPinValue <= 1030;
}

bool getButtonAPressed() {
  uint_fast16_t buttonPinValue = digitalRead(PIN_BUTTON_A);
  return buttonPinValue == HIGH;
}
#endif
