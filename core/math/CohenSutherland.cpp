#include "CohenSutherland.h"
#include <optional>
#include <tuple>

namespace CohenSutherland {

int const ComputeOutCode(const CGMath::Vec2 &point,
                         const CGMath::Vec2 &rect_min,
                         const CGMath::Vec2 &rect_max) {
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

std::optional<std::tuple<CGMath::Vec2, CGMath::Vec2>> const
CohenSutherlandLineClip(CGMath::Vec2 &point_1, CGMath::Vec2 &point_2,
                        const CGMath::Vec2 &rect_min,
                        const CGMath::Vec2 &rect_max) {

  auto outcode_1 = ComputeOutCode(point_1, rect_min, rect_max);
  auto outcode_2 = ComputeOutCode(point_2, rect_min, rect_max);

  while (true) {
    if (!(outcode_1 | outcode_2)) {
      return std::make_optional(std::make_tuple(point_1, point_2));
    } else if (outcode_1 & outcode_2) {
      return std::nullopt;
    } else {

      auto p = CGMath::Vec2{0.0f};
      auto outCodeOut = outcode_2 > outcode_1 ? outcode_2 : outcode_1;

      if (outCodeOut & OUTCODE::TOP) {
        p.x = point_1.x + (point_2.x - point_1.x) * (rect_max.y - point_1.y) /
                              (point_2.y - point_1.y);
        p.y = rect_max.y;
      } else if (outCodeOut & OUTCODE::BOTTOM) {
        p.x = point_1.x + (point_2.x - point_1.x) * (rect_min.y - point_1.y) /
                              (point_2.y - point_1.y);
        p.y = rect_min.y;
      } else if (outCodeOut & OUTCODE::RIGHT) {
        p.y = point_1.y + (point_2.y - point_1.y) * (rect_max.x - point_1.x) /
                              (point_2.x - point_1.x);
        p.x = rect_max.x;
      } else if (outCodeOut & OUTCODE::LEFT) {
        p.y = point_1.y + (point_2.y - point_1.y) * (rect_min.x - point_1.x) /
                              (point_2.x - point_1.x);
        p.x = rect_min.x;
      }

      if (outCodeOut == outcode_1) {
        point_1 = p;
        outcode_1 = ComputeOutCode(point_1, rect_min, rect_max);
      } else {
        point_2 = p;
        outcode_2 = ComputeOutCode(point_2, rect_min, rect_max);
      }
    }
  }
}

} // namespace CohenSutherland