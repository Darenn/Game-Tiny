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

#endif
