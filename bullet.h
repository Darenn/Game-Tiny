#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 3

#include "physics.h"
#include "invader.h"

typedef struct Bullet {
  SPRITE sprite;
  bool enabled = false;
} Bullet;

// TODO optimized using only one get rect function?
Rect getBulletRect(Bullet *b) {
  return Rect{b->sprite.x, b->sprite.y, b->sprite.x + 8, b->sprite.y + 8};
}

Bullet createBullet() {
  Bullet b;
  b.sprite = ssd1306_createSprite(0, 0, sizeof(shootSprite),  shootSprite);
  b.enabled = false;
  return b;
}

void kill(Bullet *bullet) {
  bullet->enabled = false;
  bullet->sprite.erase();
}

static bool processCollisionWithInvaders(Bullet *theBullet) {
  for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
      uint_fast8_t x = getPosX(i);
      uint_fast8_t y = getPosY(i);   
      if (!invaders[i].isDead && isColliding(getBulletRect(theBullet), getInvaderRect(x, y))) {
        kill(theBullet);
        killInvader(&invaders[i], i);
        compensateDead();
        drawInvaders();
        return true;
      }
    }
   return false;
}

void bulletDraw(Bullet* b) {
  b->sprite.eraseTrace();
  b->sprite.draw();
}

void bulletUpdate(Bullet* bullet) {
  if (bullet->enabled) {
    if(bullet->sprite.y >= 60 || bullet->sprite.y <= 0) {
      kill(bullet);
      return;
    }
    if(!processCollisionWithInvaders(bullet)) {
      bulletDraw(bullet);
    }
    bullet->sprite.y -= BULLET_SPEED;
  }
}




#endif
