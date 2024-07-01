#include "Renderer.h"
#include "CPU_Renderer.h"

namespace Rasterization {
Ref<Renderer> Renderer::Create(const int32_t width, const int32_t height) {
#ifdef USE_CPU_RENDERER
  return CreateRef<CPU_Renderer>(width, height);
#endif

#ifdef USE_GPU_RENDERER
  return CreateRef<CPU_Renderer>(width, height);
#endif
}
} // namespace Rasterization