#include "FrameBuffer.h"

namespace Rasterization {
FrameBuffer::FrameBuffer(const uint32_t width, const uint32_t height)
    : m_Width(width), m_Height(height), m_PixelSize(width * height) {
  ASSERT(width > 0 && height > 0);

  m_DepthAttachment = CreateScope<float[]>(m_PixelSize);
  m_ColorAttachment = CreateScope<glm::vec4[]>(m_PixelSize);
}

FrameBuffer::~FrameBuffer() {}

void FrameBuffer::SetColor(const uint32_t x, const uint32_t y,
                           const glm::vec4 &color) const {
  auto index = GetPixelIndex(x, y);
  if (index < m_PixelSize && index >= 0) {
    m_ColorAttachment[index] = color;
  } else {
    ASSERT(false);
  }
}

void FrameBuffer::SetColor(const uint32_t x, const uint32_t y,
                           const glm::vec3 &color) const {
  auto index = GetPixelIndex(x, y);
  if (index < m_PixelSize && index >= 0) {
    m_ColorAttachment[index] = glm::vec4{color, 1.0f};
  } else {
    ASSERT(false);
  }
}

glm::vec4 FrameBuffer::GetColor(const uint32_t x, const uint32_t y) const {
  auto index = GetPixelIndex(x, y);
  if (index < m_PixelSize && index >= 0) {
    return m_ColorAttachment[index];
  } else {
    ASSERT(false);
    return glm::vec4();
  }
}

void FrameBuffer::SetDepth(const uint32_t x, const uint32_t y,
                           const float depth) const {
  auto index = GetPixelIndex(x, y);
  if (index < m_PixelSize && index >= 0) {
    m_DepthAttachment[index] = depth;
  } else {
    ASSERT(false);
  }
}

float FrameBuffer::GetDepth(const uint32_t x, const uint32_t y) const {
  auto index = GetPixelIndex(x, y);
  if (index < m_PixelSize && index >= 0) {
    return m_DepthAttachment[index];
  } else {
    ASSERT(false);
    return 0.0f;
  }
}

void FrameBuffer::Clear(const glm::vec4 &color) {
  for (uint32_t i = 0; i < m_PixelSize; i++) {
    m_ColorAttachment[i] = color;
  }
}

void FrameBuffer::ClearDepth(float depth) {
  for (uint32_t i = 0; i < m_PixelSize; i++) {
    m_DepthAttachment[i] = depth;
  }
}
} // namespace Rasterization