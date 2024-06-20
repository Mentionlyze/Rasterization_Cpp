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

  float aspect = (float)width / (float)height;

  m_Camera = CreateRef<Camera>(Math::Deg2Rad(45.0f), aspect, 0.1f, 100.0f);
  m_ViewPort = ViewPort{0, 0, width, height};
}

void Renderer::DrawTriangle(const Math::Mat4 &model,
                            const Math::Vec3 (&vertices)[3],
                            const Math::Color &color) {
  std::array<Math::Vec2, 3> result;
  for (uint32_t i = 0; i < 3; i++) {

    auto frustumMat = m_Camera->GetFrustum()->GetMat();

    Math::Mat4 mvp = frustumMat * model;

    std::cout << vertices[i].x << "\n";

    Math::Vec4 vertice = Math::Vec4{vertices[i]};

    std::cout << vertice.x << "\n";

    Math::Vec4 v = mvp * vertice;

    v = 1 / v.w * v;

    auto v2 = Math::Vec2{
        float((v.x + 1.0) * 0.5 * (m_ViewPort.w - 1) + m_ViewPort.x),
        float(m_ViewPort.h - (v.y + 1.0f) * 0.5 * (m_ViewPort.h - 1) +
              m_ViewPort.y)};

    result[i] = v2;
  }

  for (uint32_t i = 0; i < 3; i++) {
    DrawLine(result[i], result[(i + 1) % 3], color);
  }
}

void Renderer::DrawLine(const Math::Vec2 &point_1, const Math::Vec2 &point_2,
                        const Math::Vec4 &color) {

  Math::Vec2 point_start = Math::Vec2{point_1.x, point_1.y};
  Math::Vec2 point_end = Math::Vec2{point_2.x, point_2.y};

  auto result = CohenSutherland::CohenSutherlandLineClip(
      point_start, point_end, Math::Vec2{0.0f},
      Math::Vec2{(float)m_Width - 1, (float)m_Height - 1});

  if (result) {
    Math::Vec2 p1, p2;
    std::tie(p1, p2) = result.value();
    DrawLineWithoutClip((int32_t)p1.x, (int32_t)p1.y, (int32_t)p2.x,
                        (int32_t)p2.y, color);
  } else {
    std::cout << "No valid tuple result" << "\n";
  }
}

void Renderer::DrawLineWithoutClip(const int32_t x0, const int32_t y0,
                                   const int32_t x1, const int32_t y1,
                                   const Math::Color &color) {
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