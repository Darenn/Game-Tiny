#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 3
#define EXPLOSION_DURATION 15 // in frame

#include "physics.h"
#include "invader.h"

typedef struct Bullet {
  SPRITE sprite;
  bool enabled = false;
  int_fast8_t explosionTimer = 0;
  bool exploding = false;
} Bullet;


// TODO optimized using only one get rect function?
Rect getBulletRect(Bullet *b) {
  return Rect{b->sprite.x, b->sprite.y, b->sprite.x + 8, b->sprite.y + 8};
}

void kill(Bullet *bullet) {
  bullet->enabled = false;
  //bullet->exploding = true;
  //bullet->explosionTimer = EXPLOSION_DURATION;
  bullet->sprite.erase();
  bullet->sprite = ssd1306_createSprite(bullet->sprite.x, bullet->sprite.y, sizeof(explosion),  explosion);
  bullet->sprite.draw();
  note(1,1);
}

static bool processCollisionWithInvaders(Bullet *theBullet) {
  for (uint_fast8_t i = 0; i < INVADERS_COUNT; ++i) {
      uint_fast8_t x = getPosX(i);
      uint_fast8_t y = getPosY(i);   
      if (!invaders[i].isDead && isColliding(getBulletRect(theBullet), getInvaderRect(x, y))) {
        killInvader(&invaders[i], i);
        compensateDead(); // compensate the loss before redrawing
        drawInvaders(); // draw the invaders before the bullet explosion
        theBullet->sprite.x = x; // To draw the explosion on the invader position
        theBullet->sprite.y = y;
        kill(theBullet);
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
    if(bullet->sprite.y >= 60 || bullet->sprite.y <= 10) {
      kill(bullet);
      return;
    }
    if(!processCollisionWithInvaders(bullet)) {
      bulletDraw(bullet);
    }
    bullet->sprite.y -= BULLET_SPEED;
  } /*else if(bullet->exploding) {
      if(bullet->explosionTimer == 0) {
         //bullet->sprite.erase();
         bullet->exploding = false;
      } else {
        --bullet->explosionTimer;
      }
  }*/
}

void shoot(Bullet * b, uint_fast8_t x, uint_fast8_t y) {
  b->sprite.erase();
  b->sprite = ssd1306_createSprite(x, y, sizeof(shootSprite),  shootSprite);
  b->enabled = true;
  b->sprite.draw();
}


#endif
