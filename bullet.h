#ifndef BULLET_H
#define BULLET_H

#define BULLET_SPEED 1

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

#endif
