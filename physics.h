#ifndef PHYSICS_H
#define PHYSICS_H

// from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection

template<class T>
struct podrect
{
    T left;
    T top;
    T right;
    T bottom;
};

template<class T>
struct rect
{
    rect() : left(), top(), right(), bottom() {}
    rect(T left, T top, T right, T bottom) : 
        left(left), top(top), right(right), bottom(bottom) {}
    template<class Point>
    rect(Point p, T width, T height) : 
      left(p.x), right(p.y), right(p.x + width), bottom(p.y + height) {}

    T left;
    T top;
    T right;
    T bottom;
};

typedef rect<int> intrect;
typedef rect<float> floatrect;

/*bool isColliding(SSD1306_RECT rect1, SSD1306_RECT rect2) {
  return rect1.x < rect2.x + rect2.right &&
     rect1.x + rect1.right > rect2.x &&
     rect1.y < rect2.y + rect2.bottom &&
     rect1.y + rect1.bottom > rect2.y;
}*/

#endif
