#ifndef BULLET_POOL_H
#define BULLET_POOL_H

#include "Bullet.h"

#define MAX_BULLET_COUNT 20

static struct BulletPool {
  Bullet bullets [MAX_BULLET_COUNT];
  uint_fast8_t index = 0;
} bulletPool;

void bulletPoolInit() {
  for(uint_fast8_t i = 0; i < MAX_BULLET_COUNT; ++i) {
     if(bulletPool.bullets[i].enabled) {
      bulletPool.bullets[i].sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);
     }
  }
}

Bullet* bulletCreate(uint_fast8_t posX, uint_fast8_t posY) {
  Bullet* b = &bulletPool.bullets[bulletPool.index++];
  b->sprite.x = posX;
  b->sprite.y = posY;
  b->enabled = true;
  if(bulletPool.index >= MAX_BULLET_COUNT) {
    bulletPool.index = 0;
  }
  return b;
}

void bulletPoolUpdate() {
  for(uint_fast8_t i = 0; i < MAX_BULLET_COUNT; ++i) {
     if(bulletPool.bullets[i].enabled) {
      bulletUpdate(&bulletPool.bullets[i]);
     }
  }
}

#endif
