#pragma once

#include "glm/glm.hpp"
#include <optional>
namespace CohenSutherland {

enum OUTCODE {
  INSIDE = 1 >> 1,
  LEFT = 1,
  RIGHT = 1 << 1,
  BOTTOM = 1 << 2,
  TOP = 1 << 3
};

int const ComputeOutCode(const glm::vec2 &point, const glm::vec2 &rect_min,
                         const glm::vec2 &rect_max);

std::optional<std::tuple<glm::vec2, glm::vec2>> const
CohenSutherlandLineClip(glm::vec2 &point_0, glm::vec2 &point_1,
                        const glm::vec2 &rect_min, const glm::vec2 &rect_max);
} // namespace CohenSutherland