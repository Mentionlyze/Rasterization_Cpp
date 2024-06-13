#include "Renderer.h"
#include <utility>

namespace Rasterization {

Renderer::Renderer(const uint32_t width, const uint32_t height) {
  m_FrameBuffer = CreateRef<FrameBuffer>(width, height);
}

void Renderer::DrawLine(const int32_t x0, const int32_t y0, const int32_t x1,
                        const int32_t y1, const Vec4 &color) {
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