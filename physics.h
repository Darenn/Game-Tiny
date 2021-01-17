#ifndef PHYSICS_H
#define PHYSICS_H

// from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

typedef struct Rect {
  int_fast8_t left;
  int_fast8_t top;
  int_fast8_t right;
  int_fast8_t bottom; 
} Rect;

bool isColliding(const SSD1306_RECT rect1, const SSD1306_RECT rect2) {
  return rect1.left < rect2.right &&
         rect1.right > rect2.left &&
         rect1.top < rect2.bottom &&
         rect1.bottom > rect2.top;
}

bool isColliding(const Rect r1, const Rect r2) {
  return r1.left < r2.right &&
         r1.right > r2.left &&
         r1.top < r2.bottom &&
         r1.bottom > r2.top;
}

#endif
