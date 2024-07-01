#pragma once

#include "math/Math.h"
#include <array>
#include <optional>
namespace Rasterization {

struct Edge {
  Math::Vec2 v1;
  Math::Vec2 v2;
};

class TrapeZoid {
public:
  TrapeZoid(const float top, const float bottom, const Edge &left,
            const Edge &right);
  ~TrapeZoid() = default;

  // clang-format off
  std::array<std::optional<TrapeZoid>, 2> const 
  static FromTriangle(const Math::Vec2 (&vertices)[3]);
  // clang-format on

public:
  float top, bottom;
  Edge left, right;
};

} // namespace Rasterization