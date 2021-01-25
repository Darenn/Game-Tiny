#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "intf/ssd1306_interface.h"


#define CLEAR_SCREEN() clearRect(0, 0, 127, 63)

/*
 * Coordinates start at 0, please do not overflow with x2 and y2.
 */
void clearRect(lcdint_t x1, lcdint_t y1, lcdint_t x2, lcdint_t y2)
{
   //attinyAssert(x1 < x2, "!: Fill rect x1 >= x2");
   //attinyAssert(y1 < y2, "!: Fill rect y1 >= y2");
   if ((lcduint_t)x1 < 0) x1 =0;
   if ((lcduint_t)y1 < 0) y1 =0;
   if ((lcduint_t)x2 >= ssd1306_displayWidth()) x2 = (lcdint_t)ssd1306_displayWidth() - 1;
   if ((lcduint_t)y2 >= ssd1306_displayHeight()) y2 = (lcdint_t)ssd1306_displayHeight() - 1;
   uint8_t bank1 = (y1 >> 3);
   uint8_t bank2 = (y2 >> 3);
   ssd1306_lcd.set_block(x1, bank1, x2 - x1 + 1);
   for (uint8_t bank = bank1; bank<=bank2; bank++)
   {
       for (uint8_t x=x1; x<=x2; x++)
       {
           ssd1306_lcd.send_pixels1(0x00000000);
       }
       ssd1306_lcd.next_page();
   }
   ssd1306_intf.stop();
}

/*const unsigned char gameTinyLogo [160] PROGMEM = {
0x00, 0xE0, 0x30, 0x28, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0xE4, 0x14, 0x0C,
0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x3E, 0x41, 0x41,
0x49, 0x3A, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x80, 0xFF, 0x00, 0x00, 0x7E, 0x09, 0x09, 0x09, 0x7E,
0x00, 0x00, 0x7F, 0x01, 0x7E, 0x01, 0x7F, 0x00, 0x00, 0x7F, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00,
0x00, 0xFF, 0x02, 0x02, 0x02, 0x12, 0x12, 0xF2, 0x12, 0x12, 0x02, 0x02, 0x02, 0xFF, 0x01, 0x00,
0xFF, 0x00, 0x00, 0x10, 0x10, 0xF0, 0x10, 0x10, 0x00, 0x00, 0xF0, 0x10, 0xE0, 0x00, 0xF0, 0x00,
0x00, 0x70, 0x80, 0x80, 0x80, 0x70, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x27,
0x20, 0x20, 0x20, 0x20, 0x20, 0x3F, 0x10, 0x08, 0x07, 0x00, 0x00, 0x04, 0x04, 0x07, 0x04, 0x04,
0x00, 0x00, 0x07, 0x00, 0x03, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00
};*/


const PROGMEM uint8_t invaderGhostIdle [] = {
  0B10100000,
  0B01110000,
  0B00101000,
  0B01111000,
  0B01111000,
  0B00101000,
  0B01110000,
  0B10100000,
};

const PROGMEM uint8_t invaderGhostMove [] = {
  0B00100000,
  0B01110000,
  0B10101000,
  0B01111000,
  0B01111000,
  0B10101000,
  0B01110000,
  0B00100000,
};

const PROGMEM uint8_t invaderPoulpeIdle [] = {
  0B00110000,
  0B00111000,
  0B10101000,
  0B01111000,
  0B01111000,
  0B10101000,
  0B00111000,
  0B00110000
};

const PROGMEM uint8_t invaderPoulpeMove [] = {
  0B10110000,
  0B01111000,
  0B10101000,
  0B01111000,
  0B01111000,
  0B10101000,
  0B01111000,
  0B10110000
};

const PROGMEM uint8_t invaderAlienIdle [] = {
  0B01000000,
  0B00101000,
  0B11010000,
  0B01100000,
  0B01100000,
  0B11010000,
  0B00101000,
  0B01000000,
};

const PROGMEM uint8_t invaderAlienMove [] = {
  0B00010000,
  0B00101000,
  0B11010000,
  0B01100000,
  0B01100000,
  0B11010000,
  0B00101000,
  0B00010000,
};

const PROGMEM uint8_t shootSprite[1] =
{
  0B00011110,
};

const PROGMEM uint8_t bulletFast1[] =
{
  0B10101000,
  0B01010100,
};

const PROGMEM uint8_t bulletFast2[] =
{
  0B01010100,
  0B10101000,
};

const PROGMEM uint8_t playerBMP[7] =
{
  0B01000000,
  0B01100000,
  0B01100000,
  0B01111110,
  0B01100000,
  0B01100000,
  0B01000000
};

const PROGMEM uint8_t playerShot[7] =
{
  0B01000000,
  0B01100000,
  0B01100000,
  0B01100000,
  0B01100000,
  0B01100000,
  0B01000000
};

const PROGMEM uint8_t explosion[] =
{
  0B01000001,
  0B00100010,
  0B10000001,
  0B10000001,
  0B00100100,
  0B01000010,
  0B10000001
};

const PROGMEM uint8_t ufoBMP[] =
{
  0B00100000,
  0B00110000,
  0B01111000,
  0B11101000,
  0B01111000,
  0B00101000, 
  0B01111000, 
  0B00101000,
  0B01111000,
  0B11101000,
  0B01111000,
  0B00110000,
  0B00100000,
};
#endif
