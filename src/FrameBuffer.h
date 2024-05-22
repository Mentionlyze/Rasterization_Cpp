#pragma once

#include "Base.h"
#include "Math.h"
#include <cstdint>
namespace Rasterization {
class FrameBuffer {
public:
  FrameBuffer(const uint32_t width, const uint32_t height);
  ~FrameBuffer();

  uint32_t GetWidth() const { return m_Width; }
  uint32_t GetHeight() const { return m_Height; }

  void SetColor(const uint32_t x, const uint32_t y, const Vec3 &color) const;
  Vec3 GetColor(const uint32_t x, const uint32_t y) const;

  void SetDepth(const uint32_t x, const uint32_t y, const float depth) const;
  float GetDepth(const uint32_t x, const uint32_t y) const;

  void Clear(const Vec3 &color = {0.0f, 0.0f, 0.0f});
  void ClearDepth(float depth = 1.0f);

private:
  uint32_t GetPixelIndex(const uint32_t x, const uint32_t y) const {
    return y * m_Width + x;
  }

private:
  uint32_t m_Width, m_Height;
  uint32_t m_PixelSize;
  Scope<float[]> m_DepthBuffer;
  Scope<Vec3[]> m_ColorBuffer;
};
} // namespace Rasterization