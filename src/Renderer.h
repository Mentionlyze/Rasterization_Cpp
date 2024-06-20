#pragma once

#include "Camera.h"
#include "FrameBuffer.h"
namespace Rasterization {

struct ViewPort {
  int32_t x, y, w, h;
};

class Renderer {
public:
  Renderer(const int32_t width, const int32_t height);
  ~Renderer() = default;

  const Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

  void Clear(const CGMath::Color &color) { m_FrameBuffer->Clear(color); }

  void ClearDepth(const float depth) { m_FrameBuffer->ClearDepth(depth); }

  void DrawTriangle(const CGMath::Mat4 model, const CGMath::Vec3 (&vertices)[3],
                    const CGMath::Color &color);

  void DrawLine(const CGMath::Vec2 &point_1, const CGMath::Vec2 &point_2,
                const CGMath::Color &color);

private:
  void DrawLineWithoutClip(const int32_t x0, const int32_t y0, const int32_t x1,
                           const int32_t y1, const CGMath::Color &color);

  int32_t m_Width, m_Height;
  Ref<FrameBuffer> m_FrameBuffer;
  Ref<Camera> m_Camera;
  ViewPort m_ViewPort;
};
} // namespace Rasterization