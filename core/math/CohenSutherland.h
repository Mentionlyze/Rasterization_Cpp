#pragma once

#include "Math.h"
#include <optional>
namespace CohenSutherland {

enum OUTCODE {
  INSIDE = 1 >> 1,
  LEFT = 1,
  RIGHT = 1 << 1,
  BOTTOM = 1 << 2,
  TOP = 1 << 3
};

int const ComputeOutCode(const Math::Vec2 &point, const Math::Vec2 &rect_min,
                         const Math::Vec2 &rect_max);

std::optional<std::tuple<Math::Vec2, Math::Vec2>> const
CohenSutherlandLineClip(Math::Vec2 &point_0, Math::Vec2 &point_1,
                        const Math::Vec2 &rect_min, const Math::Vec2 &rect_max);
} // namespace CohenSutherland