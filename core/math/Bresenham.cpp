#include "Bresenham.h"
#include "CohenSutherland.h"
#include <cstdlib>
#include <tuple>
#include <utility>

namespace Core {
Bresenham::Bresenham(Math::Vec2 &p1, Math::Vec2 &p2, const Math::Vec2 &rect_min,
                     const Math::Vec2 &rect_max) {
  auto result = CohenSutherlandLineClip(p1, p2, rect_min, rect_max);
  if (result) {
    Math::Vec2 p1, p2;
    std::tie(p1, p2) = result.value();

    auto x0 = (int32_t)p1.x;
    auto y0 = (int32_t)p1.y;
    auto x1 = (int32_t)p2.x;
    auto y1 = (int32_t)p2.y;

    auto dx = std::abs(x1 - x0);
    auto dy = std::abs(y1 - y0);
    x_Step = x1 >= x0 ? 1 : -1;
    y_Step = y1 >= y0 ? 1 : -1;
    x = x0;
    y = y0;

    steep = dx < dy ? 1 : -1;

    final_X = dx < dy ? y1 : x1;

    if (dx < dy) {
      std::swap(dx, dy);
      std::swap(x, y);
      std::swap(x_Step, y_Step);
    }

    e = -dx;
    step = 2 * dy;
    desc = -2 * dx;
  }
}

Bresenham::~Bresenham() {}
} // namespace Core