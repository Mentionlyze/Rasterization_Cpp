#pragma once

#include "base/Base.h"
#include "math/Math.h"
#include <cstdint>

namespace Rasterization {
class FrameBuffer {
public:
  FrameBuffer(const uint32_t width, const uint32_t height);
  ~FrameBuffer();

  uint32_t GetWidth() const { return m_Width; }
  uint32_t GetHeight() const { return m_Height; }

  void SetColor(const uint32_t x, const uint32_t y,
                const Math::Color &color) const;
  Math::Color GetColor(const uint32_t x, const uint32_t y) const;

  void SetDepth(const uint32_t x, const uint32_t y, const float depth) const;
  float GetDepth(const uint32_t x, const uint32_t y) const;

  void Clear(const Math::Color &color = {0.0f, 0.0f, 0.0f, 1.0f});
  void ClearDepth(float depth = 1.0f);

private:
  uint32_t GetPixelIndex(const uint32_t x, const uint32_t y) const {
    return y * m_Width + x;
  }

private:
  uint32_t m_Width, m_Height;
  uint32_t m_PixelSize;
  Scope<float[]> m_DepthAttachment;
  Scope<Math::Color[]> m_ColorAttachment;
};
} // namespace Rasterization