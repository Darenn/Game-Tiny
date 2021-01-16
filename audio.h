#ifndef AUDIO_H
#define AUDIO_H

#define PIN_BUZZER PB1
const int Output = PB1;                                   // Can be 1 or 4

// Cater for 16MHz, 8MHz, or 1MHz clock:
const int Clock = ((F_CPU / 1000000UL) == 16) ? 4 : ((F_CPU / 1000000UL) == 8) ? 3 : 0;
const uint8_t scale[] PROGMEM = {239, 226, 213, 201, 190, 179, 169, 160, 151, 142, 134, 127};

void note (int n, int octave) {
  int prescaler = 8 + Clock - (octave + n / 12);
  if (prescaler < 1 || prescaler > 15 || octave == 0) prescaler = 0;
  DDRB = (DDRB & ~(1 << Output)) | (prescaler != 0) << Output;
  OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
  GTCCR = (Output == 4) << COM1B0;
  TCCR1 = 1 << CTC1 | (Output == 1) << COM1A0 | prescaler << CS10;
}

void beep(int bCount,int bDelay)
{
    for (int i = bCount*2; i>0; i--)
    {
        digitalWrite(PIN_BUZZER, i & 1);
        for(int i2 = 0; i2 < bDelay; i2++)
        {
            __asm__("nop\n\t");
#if F_CPU > 8000000
            __asm__("nop\n\t");
            __asm__("nop\n\t");
            __asm__("nop\n\t");
            __asm__("nop\n\t");
            __asm__("nop\n\t");
            __asm__("nop\n\t");
            __asm__("nop\n\t");
            __asm__("nop\n\t");
#endif
        }
    }
    digitalWrite(PIN_BUZZER,LOW);
}

#endif
