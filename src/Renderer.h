#pragma once

#include "Base.h"
#include "FrameBuffer.h"
#include "Math.h"
namespace Rasterization {
class Renderer {
public:
  Renderer(const uint32_t width, const uint32_t height);
  ~Renderer() = default;

  const Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

  void Clear(const Vec4 &color) { m_FrameBuffer->Clear(color); }

  void ClearDepth(float depth = 1.0) { m_FrameBuffer->ClearDepth(depth); }

private:
  Ref<FrameBuffer> m_FrameBuffer;
};
} // namespace Rasterization