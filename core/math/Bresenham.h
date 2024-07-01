#pragma once

#include "Math.h"
namespace Core {
class Bresenham {
public:
  Bresenham(const Math::Vec2 &p1, const Math::Vec2 &p2,
            const Math::Vec2 &rect_min, const Math::Vec2 &rect_max);
  ~Bresenham();

  template <class _Callback> void IteratorCallback(_Callback callback) {
    while (x != final_X) {
      if (steep > 0) {
        callback(y, x);
      } else {
        callback(x, y);
      }

      e += step;
      if (e > 0) {
        y += y_Step;
        e += desc;
      }
      x += x_Step;
    }
  }

private:
  int32_t final_X, x, y, step, desc, steep, e, x_Step, y_Step;
};

} // namespace Core