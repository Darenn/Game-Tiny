#ifndef BULLET_H
#define BULLET_H

#define PLAYER_BULLET_SPEED -3
#define EXPLOSION_DURATION 15 // in frame
#define FAST_BULLET_SPEED 1

#include "physics.h"

typedef struct Bullet {
  SPRITE sprite;
  int_fast8_t directionnalSpeed:7;
  bool enabled:1;
} Bullet;

Rect getBulletRect(Bullet *b) {
  return Rect{b->sprite.x, b->sprite.y, b->sprite.x + 1, b->sprite.y + 6};
}

void kill(Bullet *bullet) {
  bullet->enabled = false;
  bullet->sprite.erase();
  bullet->sprite = ssd1306_createSprite(bullet->sprite.x, bullet->sprite.y, sizeof(explosion),  explosion);
  bullet->sprite.draw();
// TODO  note(1,1);
}

void bulletDraw(Bullet* b) {
  b->sprite.eraseTrace();
  b->sprite.draw();
}

void bulletUpdate(Bullet* bullet) {
  
  if (bullet->enabled) {
    if(bullet->sprite.y >= 60 || bullet->sprite.y <= 10) {
      kill(bullet);
      return;
    }
    bulletDraw(bullet);
    bullet->sprite.y += bullet->directionnalSpeed;
  } 
}

void shoot(Bullet * b, uint_fast8_t x, uint_fast8_t y) {
  b->sprite.erase();
  b->sprite = ssd1306_createSprite(x, y, sizeof(shootSprite),  shootSprite); // from explosion to bullet
  b->enabled = true;
  b->sprite.draw(); // necessary?
}

void updateFastBullet(Bullet *b) {
  /*static bool usingSprite2 = false;
  if(usingSprite2) {
    b->sprite = ssd1306_createSprite(b->sprite.x, b->sprite.y, sizeof(bulletFast1),  bulletFast1);
    //usingSprite2 = true;
  } else {
    b->sprite = ssd1306_createSprite(b->sprite.x, b->sprite.y, sizeof(bulletFast2),  bulletFast2);
    //usingSprite2 = false;
  }
  usingSprite2 = !usingSprite2;*/ // to uncomment if I still want bullet animations
  bulletUpdate(b);
}


#endif
