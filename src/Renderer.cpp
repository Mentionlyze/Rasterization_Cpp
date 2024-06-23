#include "Renderer.h"
#include "math/Bresenham.h"
#include "math/Math.h"
#include <array>
#include <cstdint>
#include <iostream>

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

    Math::Vec4 vertice =
        Math::Vec4{vertices[i].x, vertices[i].y, vertices[i].z, 1.0f};

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

  DrawLineWithoutClip(point_start, point_end, color);

  // auto result = Core::CohenSutherlandLineClip(
  //     point_start, point_end, Math::Vec2{0.0f},
  //     Math::Vec2{(float)m_Width - 1, (float)m_Height - 1});

  // if (result) {
  //   Math::Vec2 p1, p2;
  //   std::tie(p1, p2) = result.value();
  //   DrawLineWithoutClip(p1, p2, color);
  // } else {
  //   std::cout << "No valid tuple result" << "\n";
  // }
}

void Renderer::DrawLineWithoutClip(Math::Vec2 &p1, Math::Vec2 &p2,
                                   const Math::Color &color) {
  auto bresenham = Core::Bresenham{p1,
                                   p2,
                                   {(float)m_ViewPort.x, (float)m_ViewPort.y},
                                   {(float)m_ViewPort.w, (float)m_ViewPort.h}};

  bresenham.IteratorCallback(
      [&](int32_t x, int32_t y) { m_FrameBuffer->SetColor(x, y, color); });
}

} // namespace Rasterization