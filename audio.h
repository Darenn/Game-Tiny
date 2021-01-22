#ifndef AUDIO_H
#define AUDIO_H

#define PIN_BUZZER PB1                             // Can be 1 or 4

// Cater for 16MHz, 8MHz, or 1MHz clock:
const int Clock = ((F_CPU / 1000000UL) == 16) ? 4 : ((F_CPU / 1000000UL) == 8) ? 3 : 0;
const uint8_t scale[] PROGMEM = {239, 226, 213, 201, 190, 179, 169, 160, 151, 142, 134, 127};



typedef struct Note {
  uint8_t note:4;
  uint8_t octave:3;
  uint8_t duration;
} Note;

/*
 * Inspired by http://www.technoblogy.com/show?20MO and rewritten and upgraded by Thierry Costa and Darenn Keller
 */
void melody(const Note* melody)
{
  while (true)
  {
    const uint_fast8_t n      = melody->note;
    const uint_fast8_t octave = melody->octave;

    uint_fast8_t prescaler = 8 + Clock - (octave + n / 12);
    if ((prescaler & 0xf0) || octave == 0) prescaler = 0;
    DDRB = (DDRB & ~(1 << PIN_BUZZER)) | (prescaler != 0) << PIN_BUZZER;
    OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
    GTCCR = (PIN_BUZZER == 4) << COM1B0;
    TCCR1 = (1 << CTC1) | ((PIN_BUZZER == 1) << COM1A0) | (prescaler << CS10);

    const uint_fast8_t duration  = melody++->duration; 
    if (!(n|octave|duration))
    {
      return; 
    } 
    delay(duration * 100);
  }
}

const Note snd_playerExplosion[] = { Note{4,1,1}, Note{3,1,1}, Note{4,1,1} , Note{3,1,1}, Note{2,1,1}, Note{3,1,2}, Note{2,1,3}, Note{1,1,4}, Note{1,1,5}, Note{0,0,0}};
const Note snd_intro[] = {Note{4,3,2}, Note{3,3,2}, Note{2,3,2}, Note{5,3,6}, Note{0,0,0}};

#endif
