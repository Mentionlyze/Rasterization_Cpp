#include "Scanline.h"
#include <algorithm>
#include <optional>

namespace Rasterization {
TrapeZoid::TrapeZoid(const float top, const float bottom, const Edge &left,
                     const Edge &right)
    : top{top}, bottom{bottom}, left{left}, right{right} {}

std::array<std::optional<TrapeZoid>, 2> const
TrapeZoid::FromTriangle(const Math::Vec2 (&vertices)[3]) {
  auto m_Vertices =
      std::array<Math::Vec2, 3>{vertices[0], vertices[1], vertices[2]};

  std::sort(m_Vertices.begin(), m_Vertices.end(),
            [](const Math::Vec2 &next, const Math::Vec2 &prev) {
              return prev.y < next.y;
            });

  if (m_Vertices[0].x == m_Vertices[1].x == m_Vertices[2].x ||
      m_Vertices[0].y == m_Vertices[1].y == m_Vertices[2].y) {
    return {std::nullopt, std::nullopt};
  }

  if (m_Vertices[0].y == m_Vertices[1].y) {
    if (m_Vertices[0].x < m_Vertices[1].x) {
      auto result = std::array{m_Vertices[1], m_Vertices[0], m_Vertices[2]};
      m_Vertices.swap(result);
    }

    auto trap = TrapeZoid{m_Vertices[0].y, m_Vertices[2].y,
                          Edge{m_Vertices[0], m_Vertices[2]},
                          Edge{m_Vertices[1], m_Vertices[2]}};

    return {trap, std::nullopt};
  }

  if (m_Vertices[1].y == m_Vertices[2].y) {
    if (m_Vertices[1].x < m_Vertices[2].x) {
      auto result = std::array{m_Vertices[0], m_Vertices[2], m_Vertices[1]};
      m_Vertices.swap(result);
    }

    auto trap = TrapeZoid{m_Vertices[0].y, m_Vertices[2].y,
                          Edge{m_Vertices[0], m_Vertices[2]},
                          Edge{m_Vertices[1], m_Vertices[2]}};

    return {trap, std::nullopt};
  }
}
} // namespace Rasterization