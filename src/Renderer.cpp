#include "Renderer.h"
#include "math/CohenSutherland.h"
#include <array>
#include <cstdint>
#include <iostream>
#include <tuple>

namespace Rasterization {

Renderer::Renderer(const int32_t width, const int32_t height)
    : m_Width{width}, m_Height{height} {
  m_FrameBuffer = CreateRef<FrameBuffer>(width, height);
  m_Camera =
      CreateRef<Camera>(glm::radians(45.0f), width / height, 1.0f, 100.0f);
  m_ViewPort = ViewPort{0, 0, width, height};
}

void Renderer::DrawTriangle(const glm::mat4 model,
                            const glm::vec3 (&vertices)[3],
                            const glm::vec4 &color) {
  std::array<glm::vec2, 3> result;
  for (uint32_t i = 0; i < 3; i++) {

    auto frustumMat = m_Camera->GetFrustum()->GetMat();

    auto mvp = frustumMat * model;

    auto v = mvp * glm::vec4{vertices[i], 1.0f};

    v = 1 / v.w * v;

    auto v2 = glm::vec2{(v.x + 1.0) * 0.5 * (m_ViewPort.w - 1) + m_ViewPort.x,
                        m_ViewPort.h - (v.y + 1.0f) * (m_ViewPort.h - 1) +
                            m_ViewPort.y};

    result[i] = v2;
  }

  for (uint32_t i = 0; i < 3; i++) {
    DrawLine(result[i], result[i + i % 3], color);
  }
}

void Renderer::DrawLine(const glm::vec2 &point_1, const glm::vec2 &point_2,
                        const glm::vec4 &color) {

  glm::vec2 point_start = glm::vec2{point_1.x, point_1.y};
  glm::vec2 point_end = glm::vec2{point_2.x, point_2.y};

  auto result = CohenSutherland::CohenSutherlandLineClip(
      point_start, point_end, glm::vec2{0.0f},
      glm::vec2{(float)m_Width - 1, (float)m_Height - 1});

  if (result) {
    glm::vec2 p1, p2;
    std::tie(p1, p2) = result.value();
    DrawLineWithoutClip((int32_t)p1.x, (int32_t)p1.y, (int32_t)p2.x,
                        (int32_t)p2.y, color);
  } else {
    std::cout << "No valid tuple result" << "\n";
  }
}

void Renderer::DrawLineWithoutClip(const int32_t x0, const int32_t y0,
                                   const int32_t x1, const int32_t y1,
                                   const glm::vec4 &color) {
  auto dx = std::abs(x1 - x0);
  auto dy = std::abs(y1 - y0);
  auto x_Step = x1 >= x0 ? 1 : -1;
  auto y_Step = y1 >= y0 ? 1 : -1;
  auto x = x0;
  auto y = y0;

  auto steep = dx < dy ? 1 : -1;

  auto final_X = dx < dy ? y1 : x1;

  if (dx < dy) {
    std::swap(dx, dy);
    std::swap(x, y);
    std::swap(x_Step, y_Step);
  }

  auto e = -dx;
  auto step = 2 * dy;
  auto desc = -2 * dx;

  while (x != final_X) {
    if (steep > 0) {
      m_FrameBuffer->SetColor(y, x, color);
    } else {
      m_FrameBuffer->SetColor(x, y, color);
    }

    e += step;
    if (e >= 0) {
      y += y_Step;
      e += desc;
    }
    x += x_Step;
  }
}

} // namespace Rasterization