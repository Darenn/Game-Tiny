#ifndef DEBUG_H
#define DEBUG_H

#include "ssd1306.h" 


/*void DebugUtoa(uint16_t b)
{
    utoa(b,tempStr,10);
}*/

void debugDisplayInt(signed int value, int xPosition, int yPosition) {
  char tempStr[4] = {0};
  utoa(value,tempStr,10);
  ssd1306_printFixed (xPosition,  yPosition, tempStr, STYLE_NORMAL);
}

// Function to see how much ram you still have

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__
 
int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

#endif
