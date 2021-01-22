#define SET_BIT(x, pos) (x |= (1U << pos))
#define CLEAR_BIT(x, pos) (x &= (~(1U<< pos)))
#define LOWBYTE(v)   ((unsigned char) (x))
#define HIGHBYTE(v)  ((unsigned char) (((unsigned int) (x)) >> 8))

#define CHECK_BIT(x, pos) (x & (1UL << pos))
#define TOGGLE_BIT(x, pos) x ^= (1U<< pos)

#define SHELTERS_Y_POS 48

#define SHELTER_WEST_X_POS 10

uint8_t shelterBitmap[] =
{
  0B11100000,
  0B11110000,
  0B01110000,
  0B01111000,
  
  0B00111000,
  
  0B01111000,
  0B01110000,
  0B11110000,
  0B11100000,
};

typedef struct Shelter {
uint8_t x;
uint8_t y;
uint8_t* data;
} Shelter;

Shelter shelterWest {.x = SHELTER_WEST_X_POS, .y = SHELTERS_Y_POS, .data=shelterBitmap};

// x and y should be in the collision box
static bool processPixelCollisionWithShelter(Shelter* shelter, int posX, int posY) {
  int posXLocal = posX - shelter->x;
  int posYLocal = posY - shelter->y;
  int8_t* data = shelter->data;
  if(CHECK_BIT(data[posXLocal], posYLocal)) {
    TOGGLE_BIT(data[posXLocal], posYLocal);
    shelter->data = data;
    debugDisplayInt(posXLocal, 0, 40);
    debugDisplayInt(posYLocal, 0, 50);
    delay(4000);
    return true;
  } 
  return false;
}

bool processCollisionWithShelters(Bullet *theBullet) {
  Rect shelterRect = Rect{shelterWest.x, shelterWest.y, shelterWest.x + 8, shelterWest.y + 8};
  if (isColliding(getBulletRect(theBullet), shelterRect) && processPixelCollisionWithShelter(&shelterWest,theBullet->sprite.x+8, theBullet->sprite.y+8)) {
    kill(theBullet);
    return true;
  }
  return false;
}

void drawShelters() {
  /*uint8_t test[] =
    {
    0B11100000,
    0B11110000,
    0B01110000,
    0B01111000,
    
    0B00111000,
    
    0B01111000,
    0B01110000,
    0B11110000,
    0B11100000,
    };*/
  //ssd1306_drawBuffer(0, 0, 9, 1, test);
  //uint8_t buffer[3] = { 0xFF, 0x81, 0xFF };
  ssd1306_drawBuffer(shelterWest.x, SHELTERS_Y_POS/8, 9, 8, shelterWest.data);
}
