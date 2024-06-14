#pragma once

#include "Base.h"
#include "FrameBuffer.h"
namespace Rasterization {
class Renderer {
public:
  Renderer(const uint32_t width, const uint32_t height);
  ~Renderer() = default;

  const Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

  void Clear(const Math::Vec4 &color) { m_FrameBuffer->Clear(color); }

  void ClearDepth(const float depth) { m_FrameBuffer->ClearDepth(depth); }

  void DrawLine(const int32_t x0, const int32_t y0, const int32_t x1,
                const int32_t y1, const Math::Vec4 &color);
  void DrawLine(const int32_t x0, const int32_t y0, const int32_t x1,
                const int32_t y1, const Math::Vec3 &color);

private:
  Ref<FrameBuffer> m_FrameBuffer;
};
} // namespace Rasterization