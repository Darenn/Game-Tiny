extern const uint8_t TinyFont4x6[] PROGMEM;
const uint8_t TinyFont4x6[] PROGMEM =
{
#ifdef CONFIG_SSD1306_UNICODE_ENABLE
//  type|width|height|first char
    0x01, 0x04, 0x06, 0x2F,
//  unicode(2B)|count
    0x00, 0x2F, 0x1B, // unicode record
#else
//  type|width|height|first char
    0x00, 0x04, 0x06, 0x2F,
#endif
    0x00, 0x00, 0x00, 0x00, // char '/' (0x002F/47) SPACE
    0x3E, 0x22, 0x3E, 0x00, // char '0' (0x0030/48) 
    0x04, 0x3E, 0x00, 0x00, // char '1' (0x0031/49)
    0x32, 0x2A, 0x24, 0x00, // char '2' (0x0032/50)
    0x22, 0x2A, 0x36, 0x00, // char '3' (0x0033/51)
    0x0E, 0x08, 0x3E, 0x00, // char '4' (0x0034/52)
    0x2E, 0x2A, 0x3A, 0x00, // char '5' (0x0035/53)
    0x3E, 0x2A, 0x3A, 0x00, // char '6' (0x0036/54)
    0x02, 0x0A, 0x3E, 0x00, // char '7' (0x0037/55)
    0x3E, 0x2A, 0x3E, 0x00, // char '8' (0x0038/56)
    0x2E, 0x2A, 0x3E, 0x00, // char '9' (0x0039/57)
    0x3C, 0x0A, 0x3C, 0x00, // char ':' (0x003A/58) A
    0x3E, 0x2A, 0x14, 0x00, // char ';' (0x003B/59) B
    0x1C, 0x22, 0x22, 0x00, // char '<' (0x003C/60) C
    0x3E, 0x2A, 0x22, 0x00, // char '=' (0x003D/61) E
    0x1C, 0x2A, 0x3A, 0x00, // char '>' (0x003E/62) G
    0x3E, 0x08, 0x3E, 0x00, // char '?' (0x003F/63) H
    0x22, 0x3E, 0x22, 0x00, // char '@' (0x0040/64) I
    0x3E, 0x20, 0x20, 0x00, // char 'A' (0x0041/65) L
    0x3E, 0x1C, 0x3E, 0x00, // char 'B' (0x0042/66) M
    0x1C, 0x22, 0x1C, 0x00, // char 'C' (0x0043/67) O
    0x3E, 0x0A, 0x34, 0x00, // char 'D' (0x0044/68) R
    0x24, 0x2A, 0x12, 0x00, // char 'E' (0x0045/69) S
    0x02, 0x3E, 0x02, 0x00, // char 'F' (0x0046/70) T
    0x1E, 0x20, 0x3E, 0x00, // char 'G' (0x0047/71) U
    0x0E, 0x30, 0x0E, 0x00, // char 'H' (0x0048/72) V
    0x3E, 0x18, 0x3E, 0x00, // char 'I' (0x0049/73) W
#ifdef CONFIG_SSD1306_UNICODE_ENABLE
    0x00, 0x00, 0x00, // end of unicode tables
#endif
};
