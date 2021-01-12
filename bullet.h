#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 3

typedef struct Bullet {
  SPRITE sprite;
  bool enabled;
} Bullet;

void bulletUpdate(Bullet* bullet) {
  bullet->sprite.y -= BULLET_SPEED;
}

void bulletDraw(Bullet* b) {
  b->sprite.eraseTrace();
  b->sprite.draw();
}

void kill(Bullet *bullet) {
      bullet->enabled = false;
      bullet->sprite.eraseTrace();
    }

#endif
