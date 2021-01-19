#ifndef AUDIO_H
#define AUDIO_H

#define PIN_BUZZER PB1                             // Can be 1 or 4

// Cater for 16MHz, 8MHz, or 1MHz clock:
const int Clock = ((F_CPU / 1000000UL) == 16) ? 4 : ((F_CPU / 1000000UL) == 8) ? 3 : 0;
const uint8_t scale[] PROGMEM = {239, 226, 213, 201, 190, 179, 169, 160, 151, 142, 134, 127};

void note (int n, int octave) {
  int prescaler = 8 + Clock - (octave + n / 12);
  if (prescaler < 1 || prescaler > 15 || octave == 0) prescaler = 0;
  DDRB = (DDRB & ~(1 << PIN_BUZZER)) | (prescaler != 0) << PIN_BUZZER;
  OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
  GTCCR = (PIN_BUZZER == 4) << COM1B0;
  TCCR1 = 1 << CTC1 | (PIN_BUZZER == 1) << COM1A0 | prescaler << CS10;
}

#endif
