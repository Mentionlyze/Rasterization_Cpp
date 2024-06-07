#include "Renderer.h"

namespace Rasterization {

Renderer::Renderer(const uint32_t width, const uint32_t height) {
  m_FrameBuffer = CreateRef<FrameBuffer>(width, height);
}

} // namespace Rasterization