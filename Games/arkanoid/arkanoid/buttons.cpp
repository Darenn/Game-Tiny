/*
    MIT License

    Copyright (c) 2017-2018, Alexey Dynda

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "buttons.h"

#include "ssd1306.h"

//  Modifications to work with Game Tiny 

#define PIN_DPAD 7
#define PIN_BUTTONS PB3

uint_fast16_t padPinValue;
uint_fast16_t buttonPinValue;

#define IS_RIGHT_PAD_PRESSED (padPinValue >= 70) && (padPinValue <= 112) // 71 and 111
#define IS_DOWN_PAD_PRESSED (padPinValue >= 983) && (padPinValue <= 1024) // 984 and 1023
#define IS_LEFT_PAD_PRESSED (padPinValue >= 512) && (padPinValue <= 515) // 513 and 514
#define IS_UP_PAD_PRESSED (padPinValue >= 163) && (padPinValue <= 200) // 164 and 199
#define IS_A_BUTTON_PRESSED (buttonPinValue >= 70) && (buttonPinValue <= 100) // 70 and 100
#define IS_B_BUTTON_PRESSED (buttonPinValue >= 300) && (buttonPinValue <= 600) // random and 512
#define IS_START_BUTTON_PRESSED (buttonPinValue >= 170) && (buttonPinValue <= 190) // random and 184

void updateInputs() {
  padPinValue = analogRead(PIN_DPAD); // analog read is actually very optimized for at tiny
  buttonPinValue = analogRead(PIN_BUTTONS);
}

uint8_t getPressedButton(uint8_t analogPin)
{
  updateInputs();
  if(IS_RIGHT_PAD_PRESSED || IS_DOWN_PAD_PRESSED || IS_B_BUTTON_PRESSED) return BUTTON_RIGHT;
  if(IS_LEFT_PAD_PRESSED || IS_UP_PAD_PRESSED || IS_A_BUTTON_PRESSED) return BUTTON_LEFT;
/*#ifdef USE_Z_KEYPAD
    int buttonValue = analogRead(analogPin);
    if (buttonValue < 100) return BUTTON_RIGHT;  
    if (buttonValue < 200) return BUTTON_UP;
    if (buttonValue < 400) return BUTTON_DOWN;
    if (buttonValue < 600) return BUTTON_LEFT;
    if (buttonValue < 800) return BUTTON_SELECT;
#else
    if (digitalRead(RIGHT_BTN) != LOW) return BUTTON_RIGHT;
    if (digitalRead(LEFT_BTN) != LOW) return  BUTTON_LEFT;
#endif*/
    return BUTTON_NONE;
}
