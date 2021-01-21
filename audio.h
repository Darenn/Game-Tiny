#ifndef AUDIO_H
#define AUDIO_H

#define PIN_BUZZER PB1                             // Can be 1 or 4

// Cater for 16MHz, 8MHz, or 1MHz clock:
const int Clock = ((F_CPU / 1000000UL) == 16) ? 4 : ((F_CPU / 1000000UL) == 8) ? 3 : 0;
const uint8_t scale[] PROGMEM = {239, 226, 213, 201, 190, 179, 169, 160, 151, 142, 134, 127};


// http://www.technoblogy.com/show?20MO

void note (int n, int octave) {
  int prescaler = 8 + Clock - (octave + n / 12);
  if (prescaler < 1 || prescaler > 15 || octave == 0) prescaler = 0;
  DDRB = (DDRB & ~(1 << PIN_BUZZER)) | (prescaler != 0) << PIN_BUZZER;
  OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
  GTCCR = (PIN_BUZZER == 4) << COM1B0;
  TCCR1 = 1 << CTC1 | (PIN_BUZZER == 1) << COM1A0 | prescaler << CS10;
}

/*void melody(const uint8_t* melody)
{
  while (true)
  {
    uint8_t n      = *melody++;
    uint8_t octave = *melody++;

    int prescaler = 8 + Clock - (octave + n / 12);
    if (prescaler < 1 || prescaler > 15 || octave == 0) prescaler = 0;
    DDRB = (DDRB & ~(1 << PIN_BUZZER)) | (prescaler != 0) << PIN_BUZZER;
    OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
    GTCCR = (PIN_BUZZER == 4) << COM1B0;
    TCCR1 = (1 << CTC1) | ((PIN_BUZZER == 1) << COM1A0) | (prescaler << CS10);

    if (!(n|octave))
    {
      return; 
    }

    int duration  = (int)(*melody++);
    delay(duration*100);
  }
}*/

//const uint8_t snd_PlayerExplosion[] PROGMEM = { /* note, octave, delay/100 */ 4,1,1, 3,1,1, 4,1,1 , 3,1,1, 2,1,1, 3,1,2, 2,1,3, 1,1,4, 1,1,5, 0,0};

#endif
