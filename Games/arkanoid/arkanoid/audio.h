#ifndef AUDIO_H
#define AUDIO_H

#define PIN_BUZZER PB1                             // Can be 1 or 4

typedef struct Note {
  uint8_t note:4;
  uint8_t octave:3;
  uint8_t duration;
} Note;


  // Cater for 16MHz, 8MHz, or 1MHz clock:
  static const int Clock = ((F_CPU / 1000000UL) == 16) ? 4 : ((F_CPU / 1000000UL) == 8) ? 3 : 0;
  static const uint8_t scale[] PROGMEM = {238, 225, 212, 200, 189, 178, 168, 159, 150, 141, 133, 126};

void note (int n, int octave) {
  int prescaler = 8 + Clock - (octave);
  if (prescaler<1 || prescaler>15 || octave==0) prescaler = 0;
  DDRB = (DDRB & ~(1<<PIN_BUZZER)) | (prescaler != 0)<<PIN_BUZZER;
  OCR1C = pgm_read_byte(&scale[n]);
  GTCCR = (PIN_BUZZER == 4)<<COM1B0;
  TCCR1 = 1<<CTC1 | (PIN_BUZZER == 1)<<COM1A0 | prescaler<<CS10;
}

/*
 * Inspired by http://www.technoblogy.com/show?20MO and rewritten and upgraded by Thierry Costa and Darenn Keller
 * note < 12, octave <  4
 */
void melody(const Note* melody)
{
  
  while (true)
  {
    const uint_fast8_t n      = melody->note;
    const uint_fast8_t octave = melody->octave;

    note(n, octave);

    const uint_fast8_t duration  = melody++->duration; 
    if (!(n|octave|duration))
    {
      return; 
    } 
    delay(duration * 100);
  }
}
const Note snd_intro[] = {Note{1,1,1}, Note{2,1,1}, Note{3,3,1}, Note{4,3,1}, Note{9,4,2}, Note{0,0,0}};
#endif
