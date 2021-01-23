

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

// x and y should be in the collision box
static bool processPixelCollisionWithShelter(int shelterPoxX, int shelterPosY, uint8_t* data, int posX, int posY) {
  signed int posXLocal = posX - shelterPoxX;
  signed int posYLocal = posY - shelterPosY;
  uint8_t* dataCopy = data;
  if(posXLocal <0 || posYLocal <0) return false;
  if(CHECK_BIT(dataCopy[posXLocal], posYLocal)) {
    CLEAR_BIT(dataCopy[posXLocal], posYLocal);
    if(posXLocal-1 > 0) CLEAR_BIT(dataCopy[posXLocal-1], posYLocal);
    if(posXLocal+1 < SHELTER_WIDTH) CLEAR_BIT(dataCopy[posXLocal+1], posYLocal);
    if(posYLocal-1 > 0) CLEAR_BIT(dataCopy[posXLocal], posYLocal-1);
    if(posYLocal+1 < 8) CLEAR_BIT(dataCopy[posXLocal+1], posYLocal+1);
    data = dataCopy;
    return true;
  } 
  return false;
}


bool processCollisionWithShelter(Bullet *theBullet, int posX, int posY, uint8_t* data) {
  Rect shelterRect = Rect{posX, posY, posX + SHELTER_WIDTH, posY + 8};
  if (isColliding(getBulletRect(theBullet), shelterRect) && processPixelCollisionWithShelter(posX,posY, data, theBullet->sprite.x, theBullet->sprite.y+3)) {
    kill(theBullet);
    return true;
  }
  return false;
}

bool processCollisionWithShelters(Bullet *theBullet) {
  return (processCollisionWithShelter(theBullet, SHELTER_WEST_X_POS, SHELTERS_Y_POS, shelterWestBitmap) ||
  processCollisionWithShelter(theBullet, SHELTER_WEST_CENTER_X_POS, SHELTERS_Y_POS, shelterWestCenterBitmap) ||
  processCollisionWithShelter(theBullet, SHELTER_EAST_CENTER_X_POS, SHELTERS_Y_POS, shelterEastCenterBitmap) ||
  processCollisionWithShelter(theBullet, SHELTER_EAST_X_POS, SHELTERS_Y_POS, shelterEastBitmap));
}


void drawShelters() {
  ssd1306_drawBuffer(SHELTER_WEST_X_POS, SHELTERS_Y_POS/8, SHELTER_WIDTH, 8, shelterWestBitmap);
  ssd1306_drawBuffer(SHELTER_WEST_CENTER_X_POS, SHELTERS_Y_POS/8, SHELTER_WIDTH, 8, shelterWestCenterBitmap);
  ssd1306_drawBuffer(SHELTER_EAST_CENTER_X_POS, SHELTERS_Y_POS/8, SHELTER_WIDTH, 8, shelterEastCenterBitmap);
  ssd1306_drawBuffer(SHELTER_EAST_X_POS, SHELTERS_Y_POS/8, SHELTER_WIDTH, 8, shelterEastBitmap);
}
