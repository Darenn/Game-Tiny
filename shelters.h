

#define SHELTERS_Y_POS 48

#define SHELTER_WEST_X_POS 2*8
#define SHELTER_WEST_CENTER_X_POS 6*8
#define SHELTER_EAST_CENTER_X_POS 10*8
#define SHELTER_EAST_X_POS 14*8

#define SHELTER_WIDTH 16

static uint8_t shelterWestBitmap[16] =
{
  0B11111100,
  0B11111110,
  0B11111111,
  0B11111111,
  0B11111111,
  0B01111111,
  0B01111111,
  0B01111111,

  0B01111111,
  0B01111111,
  0B01111111,
  0B11111111,
  0B11111111,
  0B11111111,
  0B11111110,
  0B11111100,
};

static uint8_t shelterWestCenterBitmap[] =
{
  0B11111100,
  0B11111110,
  0B11111111,
  0B11111111,
  0B11111111,
  0B01111111,
  0B01111111,
  0B01111111,

  0B01111111,
  0B01111111,
  0B01111111,
  0B11111111,
  0B11111111,
  0B11111111,
  0B11111110,
  0B11111100,
};

static uint8_t shelterEastCenterBitmap[] =
{
  0B11111100,
  0B11111110,
  0B11111111,
  0B11111111,
  0B11111111,
  0B01111111,
  0B01111111,
  0B01111111,

  0B01111111,
  0B01111111,
  0B01111111,
  0B11111111,
  0B11111111,
  0B11111111,
  0B11111110,
  0B11111100,
};

static uint8_t shelterEastBitmap[] =
{
  0B11111100,
  0B11111110,
  0B11111111,
  0B11111111,
  0B11111111,
  0B01111111,
  0B01111111,
  0B01111111,

  0B01111111,
  0B01111111,
  0B01111111,
  0B11111111,
  0B11111111,
  0B11111111,
  0B11111110,
  0B11111100,
};

typedef struct Shelter {
uint8_t x;
uint8_t y;
uint8_t* data;
} Shelter;

#define SHELTER_COUNT 2

static Shelter shelterWest {.x = SHELTER_WEST_X_POS, .y = SHELTERS_Y_POS, .data=shelterWestBitmap};
static Shelter shelterWestCenter {.x = SHELTER_WEST_CENTER_X_POS, .y = SHELTERS_Y_POS, .data=shelterWestCenterBitmap};
//static Shelter shelterEastCenter {.x = SHELTER_EAST_CENTER_X_POS, .y = SHELTERS_Y_POS, .data=shelterEastCenterBitmap};
//static Shelter shelterEast {.x = SHELTER_EAST_X_POS, .y = SHELTERS_Y_POS, .data=shelterEastBitmap};

Shelter* shelters[4] = {&shelterWest, &shelterWestCenter};//, &shelterEastCenter, &shelterEast};

// x and y should be in the collision box
static bool processPixelCollisionWithShelter(Shelter* shelter, int posX, int posY) {
  signed int posXLocal = posX - shelter->x;
  signed int posYLocal = posY - shelter->y;
  if(posXLocal <0 || posYLocal <0) return false;
  int8_t* data = shelter->data;
  if(CHECK_BIT(data[posXLocal], posYLocal)) {
    CLEAR_BIT(data[posXLocal], posYLocal);
    if(posXLocal-1 > 0) CLEAR_BIT(data[posXLocal-1], posYLocal);
    if(posXLocal+1 < SHELTER_WIDTH) CLEAR_BIT(data[posXLocal+1], posYLocal);
    if(posYLocal-1 > 0) CLEAR_BIT(data[posXLocal], posYLocal-1);
    if(posYLocal+1 < 8) CLEAR_BIT(data[posXLocal+1], posYLocal+1);
    shelter->data = data;
    return true;
  } 
  return false;
}

bool processCollisionWithShelters(Bullet *theBullet) {
  for (uint_fast8_t i = 0; i < SHELTER_COUNT; ++i) {
    Shelter* shelter = shelters[i];
    Rect shelterRect = Rect{shelter->x, shelter->y, shelter->x + SHELTER_WIDTH, shelter->y + 8};
    if (isColliding(getBulletRect(theBullet), shelterRect) && processPixelCollisionWithShelter(shelter,theBullet->sprite.x, theBullet->sprite.y+3)) {
      kill(theBullet);
      return true;
    }
  }
  return false;
}

void drawShelters() {
  ssd1306_drawBuffer(shelterWest.x, SHELTERS_Y_POS/8, SHELTER_WIDTH, 8, shelterWest.data);
  ssd1306_drawBuffer(shelterWestCenter.x, SHELTERS_Y_POS/8, SHELTER_WIDTH, 8, shelterWestCenter.data);
  /*ssd1306_drawBuffer(shelterEastCenter.x, SHELTERS_Y_POS/8, 9, 8, shelterEastCenter.data);
  ssd1306_drawBuffer(shelterEast.x, SHELTERS_Y_POS/8, 9, 8, shelterEast.data);*/
}
