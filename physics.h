#ifndef PHYSICS_H
#define PHYSICS_H

// from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

bool isColliding(const SSD1306_RECT rect1, const SSD1306_RECT rect2) {
  return rect1.left < rect2.right &&
     rect1.right > rect2.left &&
     rect1.top < rect2.bottom &&
     rect1.bottom > rect2.top;
}

#endif
