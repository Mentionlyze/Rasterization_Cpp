#pragma once

#include "Base.h"
#include "FrameBuffer.h"
namespace Rasterization {
class Renderer {
public:
  Renderer(const int32_t width, const int32_t height);
  ~Renderer() = default;

  const Ref<FrameBuffer> GetFrameBuffer() { return m_FrameBuffer; }

  void Clear(const glm::vec4 &color) { m_FrameBuffer->Clear(color); }

  void ClearDepth(const float depth) { m_FrameBuffer->ClearDepth(depth); }

  void DrawLine(glm::vec2 point_1, glm::vec2 point_2, const glm::vec4 &color);

private:
  void DrawLineWithoutClip(const int32_t x0, const int32_t y0, const int32_t x1,
                           const int32_t y1, const glm::vec4 &color);
  void DrawLineWithoutClip(const int32_t x0, const int32_t y0, const int32_t x1,
                           const int32_t y1, const glm::vec3 &color);

  int32_t m_Width, m_Height;
  Ref<FrameBuffer> m_FrameBuffer;
};
} // namespace Rasterization