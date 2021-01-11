#ifndef GRAPHICS_H
#define GRAPHICS_H

/**
 * Soba bitmap source is generated via script from https://github.com/robertgallup/bmp2hex
 * MIT license
 */
const PROGMEM uint8_t heartImage[8] =
{
    0B00001110,
    0B00011111,
    0B00111111,
    0B01111110,
    0B01111110,
    0B00111101,
    0B00011001,
    0B00001110
};

const PROGMEM uint8_t shootSprite[3] =
{
    0B00111110,
    0B00111110,
    0B00111110,
};

const PROGMEM uint8_t playerBMP[7] =
{
    0B11111000,
    0B11111000,
    0B11111111,
    0B11111111,
    0B11111111,
    0B11111000,
    0B11111000
};

const PROGMEM uint8_t invader1[7] =
{
    0B00011000,
    0B00111000,
    0B00111111,
    0B11111111,
    0B00111111,
    0B00111000,
    0B00011000,
};
#endif
