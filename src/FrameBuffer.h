#pragma once

#include "Base.h"
#include "Math.h"

namespace Rasterization {
class FrameBuffer {
public:
  FrameBuffer(const uint32_t m_Width, const uint32_t m_Height);
  ~FrameBuffer() = default;

  uint32_t GetWidth() const { return m_Width; }
  uint32_t GetHeight() const { return m_Height; }

  void SetColor(const uint32_t x, const uint32_t y, const Vec3 &color) const;
  Vec3 GetColor(const uint32_t x, const uint32_t y) const;
  void SetDepth(const uint32_t x, const uint32_t y, const float depth) const;
  float GetDepth(const uint32_t x, const uint32_t y) const;

  void Clear(const Vec3 &color = {0.0, 0.0, 0.0});
  void ClearDepth(const float depth = 1.0);

private:
  uint32_t GetPixelIndex(const uint32_t x, const uint32_t y) const {
    return y * m_Height + m_Width;
  };

private:
  uint32_t m_Width, m_Height, m_PixelSize;
  Scope<Vec3[]> m_ColorBuffer;
  Scope<float[]> m_DepthBuffer;
};
} // namespace Rasterization