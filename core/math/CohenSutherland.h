#pragma once

#include "CGMath.h"
#include <optional>
namespace CohenSutherland {

enum OUTCODE {
  INSIDE = 1 >> 1,
  LEFT = 1,
  RIGHT = 1 << 1,
  BOTTOM = 1 << 2,
  TOP = 1 << 3
};

int const ComputeOutCode(const CGMath::Vec2 &point,
                         const CGMath::Vec2 &rect_min,
                         const CGMath::Vec2 &rect_max);

std::optional<std::tuple<CGMath::Vec2, CGMath::Vec2>> const
CohenSutherlandLineClip(CGMath::Vec2 &point_0, CGMath::Vec2 &point_1,
                        const CGMath::Vec2 &rect_min,
                        const CGMath::Vec2 &rect_max);
} // namespace CohenSutherland