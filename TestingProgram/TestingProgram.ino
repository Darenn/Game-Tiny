  // Cater for 16MHz, 8MHz, or 1MHz clock:
  static const int Clock = ((F_CPU / 1000000UL) == 16) ? 4 : ((F_CPU / 1000000UL) == 8) ? 3 : 0;
  static const uint8_t scale[] PROGMEM = {238, 225, 212, 200, 189, 178, 168, 159, 150, 141, 133, 126};

#include "ssd1306.h"

/**
     Attiny85 PINS
                    ____
     RESET(PB5)   -|_|  |- 3V
     A (PB3)      -|    |- (PB2) PAD
     SDA (PB4)    -|    |- (PB1) HP
     GND          -|____|- (PB0) SDL
*/

#define PIN_BUZZER PB1
#define PIN_DPAD 7
#define PIN_BUTTONS PB3
#define PIN_SDA PB4
#define PIN_SCL PB0

void note (int n, int octave) {
  int prescaler = 8 + Clock - (octave);
  if (prescaler<1 || prescaler>15 || octave==0) prescaler = 0;
  DDRB = (DDRB & ~(1<<PIN_BUZZER)) | (prescaler != 0)<<PIN_BUZZER;
  OCR1C = pgm_read_byte(&scale[n]);
  GTCCR = (PIN_BUZZER == 4)<<COM1B0;
  TCCR1 = 1<<CTC1 | (PIN_BUZZER == 1)<<COM1A0 | prescaler<<CS10;
}


void setup() {
  ssd1306_128x64_i2c_initEx(PIN_SCL,PIN_SDA, 0);
  //ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  DDRB |= 0b00010011;
}

void loop() {
  
  static uint16_t maxPadPin = 0;
  static uint16_t minPadPin = 2000;
  static uint8_t counter;
  static char str_buffer [30];
  
  unsigned long startLoopTime = millis();  // Save time to get 30 FPS
  ssd1306_clearScreen();
  uint16_t padPinValue = analogRead(PIN_DPAD); // analog read is actually very optimized for at tiny
  uint16_t buttonPinValue = analogRead(PIN_BUTTONS); // read form pb0
  if(padPinValue > maxPadPin) maxPadPin = padPinValue;
  if(padPinValue < minPadPin) minPadPin = padPinValue;
  
  ssd1306_printFixed_oldStyle(0, 0, "Pad Pin Value: ", STYLE_NORMAL);
  utoa(padPinValue, str_buffer, 10);
  ssd1306_printFixed_oldStyle(6 * 15, 0, str_buffer, STYLE_NORMAL);

  ssd1306_printFixed_oldStyle(0, 8, "Pad Pin MIN: ", STYLE_NORMAL);
  utoa(minPadPin, str_buffer, 10);
  ssd1306_printFixed_oldStyle(6 * 15, 8, str_buffer, STYLE_NORMAL);

  ssd1306_printFixed_oldStyle(0, 16, "Pad Pin MAX: ", STYLE_NORMAL);
  utoa(maxPadPin, str_buffer, 10);
  ssd1306_printFixed_oldStyle(6 * 15, 16, str_buffer, STYLE_NORMAL);

  
  ssd1306_printFixed_oldStyle(0, 24, "Button Pin: ", STYLE_NORMAL);
  utoa(buttonPinValue, str_buffer, 10);
  ssd1306_printFixed_oldStyle(6 * 14, 24, str_buffer, STYLE_NORMAL);
  note(++counter, 2);
  if (counter > 11) counter = 0;
  // Fix 30 FPS
  signed int timeToWait = (signed int)32 - (millis() - startLoopTime);
  if (timeToWait >= 0 && timeToWait < 33) {
    //debugDisplayInt(timeToWait, 50, 0);
    delay(timeToWait);
  } else {
    //delay (3000);
  }
}
