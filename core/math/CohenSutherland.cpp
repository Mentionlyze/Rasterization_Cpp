#include "CohenSutherland.h"
#include "math/Math.h"
#include <optional>
#include <tuple>

namespace Core {

int const ComputeOutCode(const Math::Vec2 &point, const Math::Vec2 &rect_min,
                         const Math::Vec2 &rect_max) {
  auto code = 0;

  if (point.x < rect_min.x) {
    code |= OUTCODE::LEFT;
  } else if (point.x > rect_max.x) {
    code |= OUTCODE::RIGHT;
  }

  if (point.y < rect_min.y) {
    code |= OUTCODE::BOTTOM;
  } else if (point.y > rect_max.y) {
    code |= OUTCODE::TOP;
  }
  return code;
}

std::optional<std::tuple<Math::Vec2, Math::Vec2>> const
CohenSutherlandLineClip(const Math::Vec2 &point_1, const Math::Vec2 &point_2,
                        const Math::Vec2 &rect_min,
                        const Math::Vec2 &rect_max) {

  auto p1 = Math::Vec2{point_1};
  auto p2 = Math::Vec2{point_2};

  auto outcode_1 = ComputeOutCode(p1, rect_min, rect_max);
  auto outcode_2 = ComputeOutCode(p2, rect_min, rect_max);

  while (true) {
    if (!(outcode_1 | outcode_2)) {
      return std::make_optional(std::make_tuple(p1, p2));
    } else if (outcode_1 & outcode_2) {
      return std::nullopt;
    } else {

      auto p = Math::Vec2{0.0f};
      auto outCodeOut = outcode_2 > outcode_1 ? outcode_2 : outcode_1;

      if (outCodeOut & OUTCODE::TOP) {
        p.x = p1.x + (p2.x - p1.x) * (rect_max.y - p1.y) / (p2.y - p1.y);
        p.y = rect_max.y;
      } else if (outCodeOut & OUTCODE::BOTTOM) {
        p.x = p1.x + (p2.x - p1.x) * (rect_min.y - p1.y) / (p2.y - p1.y);
        p.y = rect_min.y;
      } else if (outCodeOut & OUTCODE::RIGHT) {
        p.y = p1.y + (p2.y - p1.y) * (rect_max.x - p1.x) / (p2.x - p1.x);
        p.x = rect_max.x;
      } else if (outCodeOut & OUTCODE::LEFT) {
        p.y = p1.y + (p2.y - p1.y) * (rect_min.x - p1.x) / (p2.x - p1.x);
        p.x = rect_min.x;
      }

      if (outCodeOut == outcode_1) {
        p1 = p;
        outcode_1 = ComputeOutCode(p1, rect_min, rect_max);
      } else {
        p2 = p;
        outcode_2 = ComputeOutCode(p2, rect_min, rect_max);
      }
    }
  }
}

} // namespace Core