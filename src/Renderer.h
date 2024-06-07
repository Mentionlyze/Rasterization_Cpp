#pragma once

#include "Base.h"
#include "FrameBuffer.h"
namespace Rasterization {
class Renderer {
public:
  Renderer(const uint32_t width, const uint32_t height);
  ~Renderer() = default;

  const Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

  void Clear(const Vec4 &color) { m_FrameBuffer->Clear(color); }

  void ClearDepth(const float depth) { m_FrameBuffer->ClearDepth(depth); }

private:
  Ref<FrameBuffer> m_FrameBuffer;
};
} // namespace Rasterization