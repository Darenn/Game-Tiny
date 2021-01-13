#ifndef PHYSICS_H
#define PHYSICS_H

// from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

bool isColliding(const SSD1306_RECT rect1, const SSD1306_RECT rect2) {
  return rect1.left < rect2.right &&
         rect1.right > rect2.left &&
         rect1.top < rect2.bottom &&
         rect1.bottom > rect2.top;
}

bool isColliding(const SPRITE *const s1, const SPRITE *const s2) {
  return s1->x < s2->x + s2->w &&
         s1->x + s1->w > s2->x &&
         s1->y < s2->y + s2->w &&// TODO use HEIGHT and not W
         s1->y + s1->w > s2->y;
}

#endif
