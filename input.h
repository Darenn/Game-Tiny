#ifndef INPUTS_H
#define INPUTS_H

#define PIN_DPAD 7
#define PIN_BUTTON_ACTION PB0
#define DPAD_UP 0
#define DPAD_DOWN 1
#define DPAD_RIGHT 2
#define DPAD_LEFT 3
#define BUTTON_ACTION 4
#define BUTTON_B 5

void setup_inputs() {
  pinMode(PIN_DPAD, INPUT);
  pinMode(PIN_BUTTON_ACTION, INPUT);
}

/*
 * Depending of how you built your circuits, these values can change.
 */
bool get_button_pressed(int button_id) {
  int keyVal = analogRead(PIN_DPAD);
  int actionVal = digitalRead(PIN_BUTTON_ACTION);
  switch(button_id) {
    case DPAD_RIGHT:
      return keyVal >= 690 && keyVal <= 710;
    case DPAD_DOWN:
      return keyVal >= 480 && keyVal <= 530;
    case DPAD_LEFT:
      return keyVal >= 1 && keyVal <= 30;
    case DPAD_UP:
      return keyVal >= 850 && keyVal <= 980;
    case BUTTON_B:
      return keyVal >= 1020 && keyVal <= 1030;
    case BUTTON_ACTION:
      return actionVal == HIGH;
  }
  return false;
}
#endif
